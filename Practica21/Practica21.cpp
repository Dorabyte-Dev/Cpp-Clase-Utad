#include <list>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

using Clock = std::chrono::high_resolution_clock;
using Ms = std::chrono::duration<double, std::milli>;

class TEntity{
public:
	float x = 0.f;
	float y = 0.f;
	float dx = 1.f;
	float dy = 1.f;

	char name[32] = "Entity";
	int health = 100;
	int team = 1;
	float stats[8] = { 0.0f };
};



struct EntitySoA
{
	std::vector<float> x;
	std::vector<float> y;
	std::vector<float> dx;
	std::vector<float> dy;

	void Resize(int count)
	{
		x.resize(count);
		y.resize(count);
		dx.resize(count);
		dy.resize(count);
	}
};

const int MAX_ENTITIES = 1'000'000;
const int iFrames = 50;



template <typename TFunc>
double Measure(TFunc f)
{
	auto tStart = Clock::now();
	f();
	return Ms(Clock::now() - tStart).count();
}


int main()
{
	std::list<TEntity> list(MAX_ENTITIES);

	double listMs = Measure([&]
		{
			for(int i = 0; i < iFrames; i++)
			{
				for(TEntity& e : list)
				{
					e.x += e.dx;
					e.y += e.dy;
				}
			}
		});
	printf("List lasted %f ms.\n", listMs); //List lasted 1377.472400 ms.


	std::vector<TEntity> rawBuffer(MAX_ENTITIES);
	std::vector<TEntity*> pVector(MAX_ENTITIES);
	for(size_t i = 0; i < MAX_ENTITIES; ++i)
	{
		pVector[i] = &rawBuffer[i];
	}

	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(pVector.begin(), pVector.end(), g);

	double pVectorMs = Measure([&]
		{
			for(int f = 0; f < iFrames; ++f)
			{
				for(size_t i = 0; i < MAX_ENTITIES; ++i)
				{
					pVector[i]->x += pVector[i]->dx;
					pVector[i]->y += pVector[i]->dy;
				}
			}
		});

	printf("Unordered pVector lasted %f ms.\n", pVectorMs); //Unordered pVector lasted 756.809900 ms.
	std::vector<TEntity> vector(MAX_ENTITIES);

	double vectorMs = Measure([&]
		{
			for(int i = 0; i < iFrames; i++)
			{
				for(TEntity& e : vector)
				{
					e.x += e.dx;
					e.y += e.dy;
				}
			}
		});
	printf("Ordered vector lasted %f ms.\n", vectorMs); //Ordered vector lasted 327.245700 ms.

	EntitySoA soa;
	soa.Resize(MAX_ENTITIES);

	double SoAMs = Measure([&]
		{
			for(int i = 0; i < iFrames; i++)
			{
				for(int j = 0; j < MAX_ENTITIES; j++)
				{
					soa.x[j] += soa.dx[j];
					soa.y[j] += soa.dy[j];
				}
			}
		});

	printf("SoA lasted %f ms.\n", SoAMs); //SoA lasted 43.051000 ms.


	const int MATRIX_SIZE = 4096;
	std::vector<std::vector<int>> matrix(MATRIX_SIZE, std::vector<int>(MATRIX_SIZE, 1));

	int sumRows = 0;
	double matrixRowMs = Measure([&]
		{
			
			for(int r = 0; r < MATRIX_SIZE; ++r)
			{
				for(int c = 0; c < MATRIX_SIZE; ++c)
				{
					sumRows += matrix[r][c];
				}
			}
		});
	printf("Matrix sum %d by rows lasted %f ms.\n", sumRows, matrixRowMs); //Matrix sum 16777216 by rows lasted 4.634700 ms.

	int sumColumns = 0;
	double matrixColumnMs = Measure([&]
		{
			
			for(int c = 0; c < MATRIX_SIZE; ++c)
			{
				for(int r = 0; r < MATRIX_SIZE; ++r)
				{
					sumColumns += matrix[r][c];
				}
			}
		});
	printf("Matrix sum %d by columns lasted %f ms.\n", sumColumns, matrixColumnMs); //Matrix sum 16777216 by columns lasted 101.223300 ms.


	//Medir cada versión con std::chrono y explicar las diferencias: ¿cuántos bytes útiles trae cada línea de caché(64 bytes) en cada versión?

	// La diferencia principal entre recorrer la matrix por filas y por columnas reside en, precisamente, los bytes útiles que se pueden traer
	// en cada fallo de caché. Si la matrix es de 4096x4096, teniendo en cuenta que cada fallo trae 64 bytes adyacentes, por filas se aprovechan
	// todos estos bytes, ya que los elementos de las filas están uno al lado del otro en memoria. Sin embargo, por columnas, cada fallo de caché
	// trae únicamente 1 byte útil, ya que al traerlo por columnas se maximiza el espacio que hay entre un dato y el siguiente, separados por
	// 4095 elementos el uno del otro.
}

