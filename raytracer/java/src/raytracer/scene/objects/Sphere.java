package raytracer.scene.objects;

import raytracer.Ray;
import raytracer.RayResponse;
import raytracer.math.Vector3;

/**
 * Uma esfera, que tem uma posição (herdada de Object) e um raio.
 * 
 */
public class Sphere extends Object {
    public Vector3 center;
    public double radius;

    /**
     * *
     * Retorna um objeto do tipo RayResponse com informações sobre uma possível
     * interseção do raio com este objeto (veja o arquivo ray.h com a declaração
     * da struct RayResponse).
     *
     * O objeto response deve preencher os seguintes valores:
     *  - response.intersected, true/false indicando se houve interseção ou não
     *  - response.intersectionT, o valor T do raio (semi-reta) da primeira 
     *    interseção, caso haja mais que 1 interseção
     *  - response.intersectionPoint, contendo o ponto (x,y,z) de interseção
     *  - ray.intersectionNormal, contendo o vetor normal do objeto no
     *    ponto de interseção. A normal deve ser *normalizada* (norma = 1)
     * 
     *
     * @param ray
     * @return
     */
    @Override
    public RayResponse intersectsWith(Ray ray) {
        // Inicia uma resposta com um "intersects" falso,
        // indicando que não houve interseção
        RayResponse response = new RayResponse();
        response.intersected = false;

        // Está sempre retornando false, por isso a imagem gerada não tem nada
        // Você deve implementar este método de forma que ele retorne true/false
        // dependendo se o raio acerta ou não a esfera

        return response;
    }

    @Override
    public Vector3 getCenter() {
        return center;
    }

    @Override
    public String getGeometryName() {
        return "sphere";
    }
}
