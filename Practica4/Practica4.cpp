// ***************************************************************************************
// PRÁCTICA 4 - Un mundo con entidades (punteros a función)
//
// Cada entidad guarda un puntero a una TABLA DE FUNCIONES de su tipo:
//
//     entidad ──► m_funcs ──► [ FUNC_MOVE ] ──► MoveHorizontal()
//                             [ FUNC_DRAW ] ──► DrawBall()
//
// El bucle principal no sabe de qué tipo es cada entidad: solo llama a
// m_funcs[FUNC_MOVE] y m_funcs[FUNC_DRAW]. Cada tipo decide qué hacer.
// (Es lo mismo que hace C++ con las funciones virtuales: lo veremos en la Sesión 9.)
//
// Busca los "TODO" para ver lo que tienes que completar.
// ***************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>      // _kbhit, _getch
#include <windows.h>    // Sleep
#include "consola.h"    // gotoxy, hidecursor, clear

// ---------------------------------------------------------------------------------------
// El mundo: un rectángulo de la consola con borde. Las entidades viven DENTRO del borde:
// x entre 1 y WORLD_WIDTH-2, y entre 1 y WORLD_HEIGHT-2.
// ---------------------------------------------------------------------------------------
const int WORLD_WIDTH = 60;
const int WORLD_HEIGHT = 20;
const int FRAME_MS = 100;   // milisegundos entre fotogramas

// ---------------------------------------------------------------------------------------
// La entidad y su tabla de funciones
// ---------------------------------------------------------------------------------------
struct TEntity;
typedef void (*funcEntity)(TEntity*);   // puntero a función que recibe una entidad

// Qué función hay en cada posición de la tabla
enum EFunc
{
    FUNC_MOVE = 0,   // m_funcs[FUNC_MOVE] -> mueve la entidad un paso
    FUNC_DRAW = 1,   // m_funcs[FUNC_DRAW] -> pinta la entidad
    FUNC_COUNT       // número de funciones de la tabla
};

struct TEntity
{
    int         m_ix, m_iy;    // posición
    int         m_idx, m_idy;   // dirección de movimiento (-1, 0 o 1)
    char m_sprite;
    funcEntity* m_funcs;        // tabla de FUNC_COUNT funciones de su tipo

    TEntity(funcEntity* funcs, int x, int y, int dx = 0, int dy = 0, char sprite = 'T')
    {
        m_funcs = funcs;
        m_ix = x;   m_iy = y;
        m_idx = dx; m_idy = dy;
        m_sprite = sprite;
    }
};

// ***************************************************************************************
// EJEMPLO: tipo "pelota horizontal" (rebota de izquierda a derecha y se pinta como 'O')
// ***************************************************************************************
void MoveHorizontal(TEntity* e)
{
    e->m_ix += e->m_idx;
    if (e->m_ix <= 1 || e->m_ix >= WORLD_WIDTH - 2)
        e->m_idx = -e->m_idx;               // en el borde, cambia de sentido
}

void MoveHorizontalDouble(TEntity* e)
{
    e->m_ix += 2 * e->m_idx;
    if (e->m_ix <= 1 || e->m_ix >= WORLD_WIDTH - 2)
        e->m_idx = 2 * -e->m_idx;               // en el borde, cambia de sentido
}

void MoveDiagonal(TEntity* e)
{
    e->m_ix += e->m_idx;
    if (e->m_ix <= 1 || e->m_ix >= WORLD_WIDTH - 2)
        e->m_idx = -e->m_idx;               // en el borde, cambia de sentido

    e->m_iy += e->m_idy;
    if (e->m_iy <= 1 || e->m_iy >= WORLD_HEIGHT - 2)
        e->m_idy = -e->m_idy;
}

void MoveVertical(TEntity* e)
{
    e->m_iy += e->m_idy;
    if (e->m_iy <= 1 || e->m_iy >= WORLD_HEIGHT - 2)
        e->m_idy = -e->m_idy;               // en el borde, cambia de sentido
}

void MoveAlongBorder(TEntity* e)
{
    e->m_iy += e->m_idy;
    e->m_ix += e->m_idx;
    if (e->m_idx == 0)
    {
        if (e->m_iy <= 1)
        {
            e->m_idx = e->m_idy;               // en el borde, cambia de sentido
            e->m_idy = 0;
        }
        else if (e->m_iy >= WORLD_HEIGHT - 2)
        {
            e->m_idx = e->m_idy;               // en el borde, cambia de sentido
            e->m_idy = 0;
        }
    }
    else if (e->m_idy == 0)
    {
        if (e->m_ix <= 1)
        {
            e->m_idy = -e->m_idx;               // en el borde, cambia de sentido
            e->m_idx = 0;
        }
        else if (e->m_ix >= WORLD_WIDTH - 2)
        {
            e->m_idy = -e->m_idx;               // en el borde, cambia de sentido
            e->m_idx = 0;
        }
    }

    //

}

void DrawBall(TEntity* e)
{
    gotoxy(e->m_ix, e->m_iy);
    printf("O");
}

void DrawPointer(TEntity* e) 
{
    gotoxy(e->m_ix, e->m_iy);
    printf("*");
}

void DrawCustom(TEntity* e) 
{
    gotoxy(e->m_ix, e->m_iy);
    printf("%c", e->m_sprite);
}

// La tabla de funciones del tipo: primero mover, luego pintar (en el orden de EFunc)
funcEntity g_HorizontalBall[FUNC_COUNT] = { MoveHorizontal, DrawBall };
funcEntity g_VerticalBall[FUNC_COUNT] = { MoveVertical, DrawBall }; //Tipo añadido
funcEntity g_BorderPointer[FUNC_COUNT] = { MoveAlongBorder, DrawPointer }; //Tipo añadido
funcEntity g_DiagonalBall[FUNC_COUNT] = { MoveDiagonal, DrawCustom }; //Tipo añadido

// ***************************************************************************************
// TODO: añade al menos 3 tipos más. Cada tipo = sus funciones + su tabla.
//   - Al menos dos tipos distintos deben COMPARTIR la función de pintar
//     (por ejemplo, una pelota vertical que también usa DrawBall).
//   - Ideas: vertical, diagonal (rebota en las 4 paredes), aleatorio (rand() % 3 - 1),
//     uno que parpadea (se pinta un fotograma sí y otro no)...
// ***************************************************************************************


// ---------------------------------------------------------------------------------------
// Pinta el borde del mundo
// ---------------------------------------------------------------------------------------
void DrawWorld()
{
    for (int x = 0; x < WORLD_WIDTH; ++x)
    {
        gotoxy(x, 0);                printf("-");
        gotoxy(x, WORLD_HEIGHT - 1); printf("-");
    }
    for (int y = 1; y < WORLD_HEIGHT - 1; ++y)
    {
        gotoxy(0, y);                printf("|");
        gotoxy(WORLD_WIDTH - 1, y);  printf("|");
    }
    gotoxy(2, WORLD_HEIGHT);
    printf("ESC para salir");
}

// ***************************************************************************************
// MAIN
// ***************************************************************************************
const int MAX_ENTITIES = 32;

int main()
{
    hidecursor();

    // 1. Crear las entidades con new y guardarlas en la tabla del mundo
    TEntity* entities[MAX_ENTITIES] = {};
    int numEntities = 0;

    // TODO: crear varias entidades de cada uno de vuestros tipos
    entities[numEntities++] = new TEntity(g_HorizontalBall, 5, 3, 1, 0);
    entities[numEntities++] = new TEntity(g_HorizontalBall, 40, 10, -1, 0);
    entities[numEntities++] = new TEntity(g_BorderPointer, 30, 7, 0, 1);
    entities[numEntities++] = new TEntity(g_BorderPointer, 3, 15, 2, 0);
    entities[numEntities++] = new TEntity(g_DiagonalBall, 5, 8, 2, 2, 'D');
    entities[numEntities++] = new TEntity(g_DiagonalBall, 15, 7, 1, 2, '3');
    

    // 2. Bucle del juego: se repite hasta pulsar ESC
    bool bExit = false;
    while (!bExit)
    {
        if (_kbhit() && _getch() == 27)     // 27 = tecla ESC
            bExit = true;

        // Mover todas: se llama a la función que hay en la posición FUNC_MOVE de su tabla
        for (int i = 0; i < numEntities; ++i)
            entities[i]->m_funcs[FUNC_MOVE](entities[i]);

        // Pintar: borrar la pantalla, pintar el mundo y luego todas las entidades
        clear();
        DrawWorld();
        // TODO: pintar todas las entidades llamando a la función FUNC_DRAW de su tabla
        for (int i = 0; i < numEntities; ++i) 
        {
            entities[i]->m_funcs[FUNC_DRAW](entities[i]);
        }

        Sleep(FRAME_MS);
    }

    // 3. Liberar la memoria
    // TODO: delete de cada entidad creada con new
    for (int i = 0; i < numEntities; ++i)
    {
        delete entities[i];
    }
    clear();
    return 0;
}
