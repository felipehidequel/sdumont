#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=24
#SBATCH -p cpu_dev
#SBATCH -J exemplo
#SBATCH --exclusive

echo $SLUM_JOB_NODELIST

cd /scratch/pex1272-ufersa/bruno.silva4/teste_parallel

module load gcc/14.2.0_sequana
module load openmpi/gnu/4.1.1_sequana

mpirun -np 4 ./main.exe 