#!/bin/bash
#SBATCH -p sequana_cpu 
#SBATCH --nodes=4
#SBATCH --cpus-per-task=24
#SBATCH --time=00:10:00
#SBATCH --output=saida_%j.out
#SBATCH --error=err%j.out
#SBATCH --job-name=seminario-pcd

## carrega modulos necessários
module load openmpi/gnu/4.1.1_sequana

echo $SLURM_JOB_NODELIST
nodeset -e $SLURM_JOB_NODELIST

cd $SLURM_SUBMIT_DIR

EXEC=/scratch/semipcd/sdumount/main

/usr/bin/ldd $EXEC

srun $EXEC