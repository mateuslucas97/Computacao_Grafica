package raytracer.io.objects;

import java.util.HashMap;
import java.util.Scanner;
import raytracer.scene.Scene;
import raytracer.scene.objects.Object;

/**
 *
 */
public final class ObjectBuilder {
    
    private static ObjectBuilder INSTANCE = null;
    private final HashMap<String, ObjectFactory> factories;
    
    private ObjectBuilder() {
        factories = new HashMap<>();
        factories.put("sphere", new SphereFactory());
        // adicionar novos objetos e suas fábricas aqui
    }
    
    public static ObjectBuilder getInstance() {
        if (INSTANCE == null) {
            INSTANCE = new ObjectBuilder();
        }
        return INSTANCE;
    }
    
    public Object buildFromDescription(Scanner scanner, Scene scene) {
        int pygmentId = scanner.nextInt();
        int materialId = scanner.nextInt();
        String type = scanner.next();
        
        // determina qual fábrica de objetos usar, dado o tipo escrito
        // no arquivo texto. Depois o constrói, deixando-o consumir os 
        // parâmetros daquela linha conforme sua fábrica precisa
        // eg, esfera precisa de x, y, z e raio
        // eg, cilindro precisa x, y, z (do centro), altura e raio
        // eg, triângulo precisa de x, y, z de cada vértice
        ObjectFactory factory = factories.get(type);
        Object object = factory.setupObject(scanner);
        
        // propriedades comuns a todos os objetos
        object.pygment = scene.pygments.get(pygmentId);
        object.material = scene.materials.get(materialId);

        return object;
    }
}
