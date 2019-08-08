package raytracer.scene;

import raytracer.Ray;
import raytracer.RayResponse;
import raytracer.math.Constants;
import raytracer.math.Vector3;

public class Object {

    public Pygment pygment;
    public Material material;
    public String type;
    public Vector3 position;
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
    public RayResponse intersectsWith(Ray ray) {
        // Inicia uma resposta com um "intersects" falso,
        // indicando que não houve interseção
        RayResponse response = new RayResponse();
        response.intersected = false;

        // Está sempre retornando false, por isso a imagem gerada não tem nada
        // Você deve implementar este método de forma que ele retorne true/false
        // dependendo se o raio acerta ou não a esfera
        
        Vector3 u = ray.v.normalized();
        Vector3 p = position.diff(ray.p0);
        double a,b,c;
        a = 1;
        b = -2*u.dotProduct(p);
        c = (p.dotProduct(p) - Math.pow(this.radius,2));
        
        double delta = 0;
        
        delta = Math.pow(b, 2) - 4 * a * c; 
        
        double t1 = 0;
        double t2 = 0;
        t1 = (-b - Math.sqrt(Math.pow(b, 2) - 4* a * c)) / 2 * a;
        t2 = (-b + Math.sqrt(Math.pow(b, 2) - 4* a * c)) / 2 * a;
        response.intersectionPoint = new Vector3();
        response.intersectionNormal = new Vector3();
        if(delta < 0){
            return response;
        }
        else{
            if(t1 > 0){
                response.intersected = true;
                response.intersectionT = t1;
                response.intersectionPoint.x = ray.p0.x + t1 * ray.v.x;
                
            }
            else{
                response.intersected = true;
                response.intersectionT = t2;
                response.intersectionPoint.z = ray.p0.z + t2* ray.v.z;
            }
        }
                       
     return response;
    }

}
