#!/bin/bash
#SBATCH --job-name=randomised_mj
#SBATCH --partition=iceq
#SBATCH --nodes=4
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=8
#SBATCH --mem=1000
#SBATCH --time=00:05:00
#SBATCH --mail-type=FAIL


export OMP_NUM_THREADS="8"

echo "Job $SLURM_JOB_NAME on nodes:"

echo ""
time ./pso_test
echo "Job finished"
