/** Decoupled IBPM solver.
 * \file main.cpp
 */

#include <iomanip>
#include <sys/stat.h>

#include <petsc.h>

#include <yaml-cpp/yaml.h>

#include "decoupledibpm.h"
#include "CartesianMesh.h"
#include "FlowDescription.h"
#include "SimulationParameters.h"
#include "BodyPack.h"
#include "parser.h"


int main(int argc, char **argv)
{
	PetscErrorCode ierr;

	ierr = PetscInitialize(&argc, &argv, nullptr, nullptr); CHKERRQ(ierr);

	SimulationParameters params;
	FlowDescription flow;
	CartesianMesh mesh;
	BodyPack bodies;
	YAML::Node config;
	char path[PETSC_MAX_PATH_LEN];
	std::string directory,
	            solutionDirectory,
							configpath;
	PetscBool flg;

	// parse command-line looking for simulation directory and configuration path
	directory = ".";
	ierr = PetscOptionsGetString(nullptr, nullptr, "-directory",
	                             path, sizeof(path), &flg); CHKERRQ(ierr);
	if (flg)
		directory = path;
	solutionDirectory = directory + "/solution";
	mkdir(solutionDirectory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	configpath = directory + "/config.yaml";
	ierr = PetscOptionsGetString(nullptr, nullptr,"-config",
	                             path, sizeof(path), &flg); CHKERRQ(ierr);
	if (flg)
		configpath = path;

	// parse configuration file
	ierr = parser::parseYAMLConfigFile(configpath, config); CHKERRQ(ierr);

	ierr = params.init(PETSC_COMM_WORLD,
	                   config["simulationParameters"], directory); CHKERRQ(ierr);
	ierr = params.printInfo(); CHKERRQ(ierr);

	ierr = flow.init(PETSC_COMM_WORLD,
	                 config["flowDescription"]); CHKERRQ(ierr);
	ierr = flow.printInfo(); CHKERRQ(ierr);

	ierr = mesh.init(PETSC_COMM_WORLD,
	                 config["cartesianMesh"], flow.BCInfo,
	                 params.output.format); CHKERRQ(ierr);
	ierr = mesh.printInfo(); CHKERRQ(ierr);
	ierr = mesh.write(params.caseDir, "grid"); CHKERRQ(ierr);

	ierr = bodies.init(mesh, config["bodies"]); CHKERRQ(ierr);
	ierr = bodies.printInfo(); CHKERRQ(ierr);
	
	DecoupledIBPMSolver solver = DecoupledIBPMSolver(
			mesh, flow, params, bodies); CHKERRQ(ierr);

	ierr = solver.initialize(); CHKERRQ(ierr);

	PetscInt start = params.step.nStart,
	         end = params.step.nStart + params.step.nTotal,
	         nsave = params.step.nSave;
	PetscReal time = params.step.nStart * params.step.dt;
	std::string iterationsFile = directory + "/iterations.txt";
	for (int ite=start+1; ite<=end; ite++)
	{
		time += params.step.dt;
		ierr = solver.solve(); CHKERRQ(ierr);
		ierr = solver.writeIterations(ite, iterationsFile); CHKERRQ(ierr);
		if (ite % nsave == 0)
		{
			ierr = PetscPrintf(PETSC_COMM_WORLD,
			                   "[time-step %d] Writing solution... ",
			                   ite); CHKERRQ(ierr);
			std::stringstream ss;
			ss << std::setfill('0') << std::setw(7) << ite;
			ierr = solver.write(solutionDirectory,
			                    ss.str()); CHKERRQ(ierr);
			ierr = PetscPrintf(PETSC_COMM_WORLD, "done\n"); CHKERRQ(ierr);
		}
		ierr = solver.writeIntegratedForces(
				time, params.caseDir, "forces"); CHKERRQ(ierr);
	}

	ierr = solver.finalize(); CHKERRQ(ierr);

	ierr = PetscFinalize(); CHKERRQ(ierr);
	
	return 0;
} // main
