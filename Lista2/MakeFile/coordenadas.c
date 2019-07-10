#include "coordenadas.h"
#include <math.h>
#include <stdio.h>

/// multiplica um vetor por um escalar
/// este é um exemplo entregue pronto pra você ;)
vetor multiplicaPorEscalar(vetor v, escalar alpha)
{
    vetor resultado =
    {
        v.x * alpha,
        v.y * alpha,
        v.z * alpha,
        v.w * alpha
    };
    return resultado;
}

vetor somaVetorComVetor(vetor v, vetor u)
{
    v.x += u.x;
    v.y += u.y;
    v.z += u.z;
    v.w += u.w;
    vetor resultado = v;
    return resultado;
}

vetor diferencaVetorComVetor(vetor v, vetor u)
{
     v.x -= u.x;
    v.y -= u.y;
    v.z -= u.z;
    v.w -= u.w;
    vetor resultado = v;
    return resultado;
}

vetor diferencaEntrePontos(ponto p, ponto q)
{
    
    vetor resultado = {p.x -= q.x,p.y -= q.y,p.z -= q.z,p.w -= q.w};
    return resultado;
}

ponto somaPontoComVetor(ponto p, vetor v)
{
    p.x += v.x;
    p.y += v.y;
    p.z += v.z;
    p.w += v.w;
    ponto resultado = p;
    return resultado;
}

escalar normaDoVetor(vetor v)
{
    
    escalar resultado = sqrt(v.x*v.x + v.y*v.y + v.z*v.z +v.w*v.w);
    return resultado;
}

vetor normalizado(vetor v)
{
    escalar norma = sqrt(v.x*v.x + v.y*v.y + v.z*v.z +v.w*v.w);
    
    v.x /= norma;
    v.y /= norma;
    v.z /= norma;
    v.w /= norma;
    vetor resultado = v;
    return resultado;
}

escalar distanciaEntrePontos(ponto p, ponto q)
{
    
    escalar resultado = sqrt((q.x-p.x)*(q.x-p.x) + (q.y-p.y)*(q.y-p.y) + (q.z-p.z)*(q.z-p.z) + (q.w-p.w)*(q.w-p.w));
    return resultado;
}

escalar produtoEscalar(vetor v, vetor u)
{
    
    escalar resultado = v.x*u.x + v.y*u.y + v.z*u.z + v.w*u.w;
    return resultado;
}

vetor produtoVetorial(vetor v, vetor u)
{
    
    vetor resultado = v;
    resultado.x = (v.y*u.z) - (v.z*u.y);
    resultado.y = (v.z*u.x) - (v.x*u.z);
    resultado.z = (v.x*u.y) - (v.y*u.x);
    resultado.w = 0;
    return resultado;
}

///
/// Referências: http://localhost:8080/classes/geometry/#30
escalar anguloEntreVetores(vetor v, vetor u)
{
    
    escalar resultado = acos(produtoEscalar(v,u)/(normaDoVetor(v)*normaDoVetor(u)));
    return resultado;
}

///
/// Referências: http://localhost:8080/classes/geometry/#22
ponto combinacaoAfim2Pontos(ponto p, ponto q, escalar alpha)
{
   
    p.x *= alpha;
    p.y *= alpha;
    p.z *= alpha;
    p.w *= alpha;

    q.x *= alpha;
    q.y *= alpha;
    q.z *= alpha;
    q.w *= alpha;

    p.x += q.x;
    p.y += q.y;
    p.z += q.z;
    p.w += q.w;
    ponto resultado =p;
    return resultado;
}

/// Imprime um vetor ou ponto no terminal
/// Uso:
///   vetor r = somaVetorComVetor(a, b);
///   imprime("vetor r", r);
void imprime(struct coordenadas c, char* nome)
{
    printf("%s = { %.2f, %.2f, %.2f, %.2f }\n", nome, c.x, c.y, c.z, c.w);
}
