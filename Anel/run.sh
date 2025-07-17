#!/bin/bash
#SBATCH --nodes=4
#SBATCH --time=00:10:00
#SBATCH --cpus-per-task=24
#SBATCH -p sequana_cpu_dev
#SBATCH -J exemplo
#SBATCH --exclusive

echo $SLUM_JOB_NODELIST

cd /scratch/pex1272-ufersa/bruno.silva7/sdumont

module load gcc/14.2.0_sequana
module load openmpi/gnu/4.1.1_sequana

mpicxx -fopenmp anel.c -o main.exe
mpirun -np 4 ./main.exe