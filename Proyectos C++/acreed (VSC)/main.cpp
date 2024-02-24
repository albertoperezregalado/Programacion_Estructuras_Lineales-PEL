#include "pel_print.hpp" //biblioteca propia de nuestra asignatura(espacionde nombre pel)

//ISO C++23:
#include <cstdlib> //contiene las macros EXIT_SUCCESS y EXIT_FAILURE
#include <string> //cadena de caracteres estandar
#include <fstream> //flujos i/o a ficheros, nos permite leer y escribir en ficheros
#include <vector> // contenedor secuencial por defecto
#include <algorithm>//algoritmos de ordenacion, particion, busqueda,...
#include <ranges> //contiene vistas estandar

//biblioteca de terceros
#include <nlohmann/json.hpp> // serialización deserialización de objetos json

/*

Objetivo: Se proporciona un fichero JSON Lines que contiene el estado en que un jugador guardó su anterior partida en un videojuego. El fichero almacena el estado de avance en el ataque a un campamento militar. Puedes descargarlo desde la documentación asociada a este ejercicio (véase el archivo military_camp.jsonl proporcionado más abajo).

Cada línea JSON contiene el nombre ("name") del tipo de enemigo u objetivo del campamento (strings "soldier", "leader", "secret weapon" o "treasure"), si éste ha sido ya eliminado o adquirido (bool "achieved"), su nivel de dificultad (int "level") y su posición en el mapa (array de tres doubles "location"). Nos proponemos:

Guardar la información del fichero en un vector estándar de objetos. Para ello, definiremos un agregado Target que almacene los datos proporcionados por cada enemigo/objetivo.
Para cada tipo de enemigo/objetivo, imprimir en la terminal cuántos targets han sido ya completados, así como el total de ellos (completados o no) presentes en el campamento (véase la imagen inferior derecha). Garantizaremos que los nombres de los distintos tipos de enemigos/objetivos aparezcan ordenados lexicográficamente.
Nota: Emplearemos la biblioteca de rangos del lenguaje C++23 el fin de adoptar un estilo funcional de programación, utilizando en particular la vista std::views::chunk_by.

*/
/*
//funcion para meter dentro del chunk, que compara 2 enteros
auto equal_to(int i, int j) -> bool{
    //compara de dos en dos los elementos del array
    return i == j;
}

auto main() -> int{

    auto nums = std::vector<int>{3, 1, 2, 1, 3, 2, 1, 3, 1, 1, 3};
    std::ranges::sort(nums);//ordenar el array de menor a mayor
    //ahora para saber cuantos numeros distintos ahi, iremos saltando de bloque en bloque de numeros distintos
    //for (int const& n : nums ){ // poniendo const&  evito la copia de los datos que viven en el vector y después de 
    for (auto n : nums | std::views::chunk_by(equal_to)){ // con | ponemos la vista que queremos y le pasamos a chunk la funcion que compara 2 valores
        //pel::println("{}",n); //los valores que tiene
        //voy a ver la primera casilla de cada bloque para saber que numero hay en ese bloque
        auto first = std::ranges::begin(n);
        
        pel::println("{} ----> {} veces", *first, std::ranges::distance(n));
        

    }
}
*/

struct Target { //clase donde todo el público, hay que poner el mismo nombre de variable que el del JSON
    std::string name;    
    bool achieved;
    
    //resto de campos del JSON, pero estas no hacen falta para el ejercicio
    int level;
    std::array<double, 3> location;
};

//MACRO
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Target, name, achieved)

//funcion para meter dentro del chunk, que compara 2 casillas, en este caso 2 Targets
auto same_name(Target t1, Target t2) -> bool{
    return t1.name == t2.name;
}

//ESTE MAIN ES PARA LA LECTURA DEL JSON
auto main() -> int{

    auto ifs = std::ifstream{"../../military_camp.jsonl", std::iostream::binary};//al poner std::iostream::binary nos aseguramos de que funciona en windows, mac y linux
    //comprobamos si el flujo se ha abierto correctamente
    if(!ifs){//negamos el objeto
        pel::println("Lo siento, no se ha podido abrir el fichero JSON");
        return EXIT_FAILURE;
    }

    //vector de Taget, vacio, donde ir almacenando cada Target y no perderlo en el bucle while
    auto targets = std::vector<Target>{};


    auto ln = std::string{}; //string auxiliar donde almacenara las lineas del fichero
    //creamos un bucle while, que procese el JSON linea a linea
    while (std::getline(ifs, ln)){//cuando getline devuelva un false, saldremos del while
        //deserializamos la información del objeto JSON en el string ln y obtenemos un Tarjet con la info relevante en la linea
        Target t = nlohmann::json::parse(ln).get<Target>(); //comprobamos que este bien formateado el JSON, si esta mal devuelve una excepción
        pel::println("name: {} | achieved: {}", t.name, t.achieved);//imprimimos Tarjet original
        //guardamos una copia del Target en el vector 'targets'
        targets.push_back(t);//introduce un nuevo objeto target al final del vector
    }

    //cerramos el flujo con el fichero, ya que tenemos la info guardada en el fichero
    ifs.close();

    //ordenamos el vector de targets por orden alfabetico de tipo de enemigo (name)
    std::ranges::sort(targets, std::ranges::less{}, &Target::name); //less o greater ordena de menor a mayor o viceversa

    //si queremos ver todo lo que tiene el bucle for
    for (Target const& t : targets){
        pel::println("- name: {} | achieved: {}", t.name, t.achieved);//imprimimos Tarjet resultado
    }

    //bucle for que visita cada subhrupo del vector de enemigos de indentico tipo (name)
    for (auto target_grp : targets | std::views::chunk_by(same_name)){//para que identifique los grupos de enemigos que hay
        
        auto name = std::ranges::begin(target_grp)->name;//para obtener el primer valor de cada bloque del tipo de enemigo
        auto num_targets = std::ranges::size(target_grp);//para obtener cuantos hay de cada tipo

        //ahora verificamos target a target los elementos que esten en true para cada tipo
        auto counter = int{0};
        for (Target t : target_grp){
            if(t.achieved == true){
                ++counter;      
            }            
        }
        //todo esto de counter, el for y el if, se puede sustituir por el algoritmo: (que hace lo mismo)
        auto counter2 = std::ranges::count_if(target_grp, &Target::achieved);
        
        pel::println("{} ----> {} / {}", name, counter, num_targets);
        pel::println("- {} ----> {} / {}", name, counter2, num_targets);

        //para formatear un poco el output
        //por ejemplo 15 cacteres vacios (justificado a la derecha >), (al centro ^), (a la izquierda <)
        pel::println("- {:>15} ----> {} / {}", name, counter2, num_targets);
    }
    
}
