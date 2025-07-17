#include <iostream>
#include <mpi.h>
#include <omp.h>

typedef long long int ll;

double monte_carlo_p(ll num_lancamentos);
double monte_carlo(ll num_lancamentos);
void input(int rank, int size, ll &num_lanc, MPI_Comm comm, ll &local_lanc,
           char *argv[]);

int main(int argc, char *argv[]) {

  ll num_lancamentos, local_lanc;
  double qtd_local, qtd_global;
  double s, e;
  int rank, size;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    if (argc < 2) {
      std::cout << "Usage: run.sh <numero de lançamentos>" << std::endl;
      MPI_Abort(MPI_COMM_WORLD, 1);
    }
  }

  input(rank, size, num_lancamentos, MPI_COMM_WORLD, local_lanc, argv);

  std::cout << "Rank " << rank << " with localN: " << local_lanc << " of "
            << num_lancamentos << std::endl;

  MPI_Barrier(MPI_COMM_WORLD);
  s = MPI_Wtime();
  qtd_local = monte_carlo_p(local_lanc);

  MPI_Reduce(&qtd_local, &qtd_global, 1, MPI_DOUBLE, MPI_SUM, 0,
             MPI_COMM_WORLD);
  e = MPI_Wtime();

  double local_time = e - s;
  double max_time;

  MPI_Reduce(&local_time, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    std::cout << "Estimativa de pi: " << qtd_global / size << std::endl;
    std::cout << "Tempo Paralelo: " << max_time << std::endl;
  }

  MPI_Finalize();
  return 0;
}

void input(int rank, int size, ll &num_lanc, MPI_Comm comm, ll &local_lanc,
           char *argv[]) {
  if (rank == 0) {
    num_lanc = std::atoi(argv[1]);
  }

  MPI_Bcast(&num_lanc, 1, MPI_LONG_LONG_INT, 0, comm);

  int rest = num_lanc % size;
  local_lanc = (num_lanc / size) + (rank < rest);
}

double monte_carlo_p(ll num_lancamentos) {
  ll qtd_no_circulo = 0;

#pragma omp parallel default(none) reduction(+ : qtd_no_circulo) shared(num_lancamentos)
  {
    unsigned seed = omp_get_thread_num() + 1234;
    double x, y, distancia_quadrada;

#pragma omp for
    for (ll lancamento = 0; lancamento < num_lancamentos; lancamento++) {
      x = rand_r(&seed) / (double)RAND_MAX * 2 - 1;
      y = rand_r(&seed) / (double)RAND_MAX * 2 - 1;
      distancia_quadrada = x * x + y * y;

      if (distancia_quadrada <= 1)
        qtd_no_circulo++;
    }
  }

  return 4 * qtd_no_circulo / ((double)num_lancamentos);
}

double monte_carlo(ll num_lancamentos) {
  ll qtd_no_circulo = 0;
  double x, y, distancia_quadrada;
  for (ll lancamento = 0; lancamento < num_lancamentos; lancamento++) {
    x = rand() / (double)RAND_MAX * 2 - 1;
    y = rand() / (double)RAND_MAX * 2 - 1;
    distancia_quadrada = x * x + y * y;

    if (distancia_quadrada <= 1)
      qtd_no_circulo++;
  }

  return 4 * qtd_no_circulo / ((double)num_lancamentos);
}