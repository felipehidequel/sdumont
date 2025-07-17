#!/bin/bash
#SBATCH -p sequana_cpu 
#SBATCH --nodes=4
#SBATCH --cpus-per-task=24
#SBATCH --time=00:10:00
#SBATCH --output=saida_%j.out
#SBATCH --error=err%j.out
#SBATCH --job-name=seminario-pcd

## carrega modulos necessários
# module load openmpi/gnu/4.1.1_sequana
module load openmpi/gnu/4.1.4+gcc-12.4_sequana

echo $SLURM_JOB_NODELIST
nodeset -e $SLURM_JOB_NODELIST

cd $SLURM_SUBMIT_DIR

# tem que ser o caminho que do executavel na pasta de vocês
EXEC=/scratch/pex1272-ufersa/felipe.silva4/sdumont/main

/usr/bin/ldd $EXEC

N_LANCAMENTOS=$1

srun $EXEC $N_LANCAMENTOS