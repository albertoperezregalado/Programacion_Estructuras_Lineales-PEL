#include <cstdlib> //contiene las macros EXIT_SUCESS y EXIT_FAILURE
#include <format> //permite el formato de texto
#include <iostream> // contiene los objetos globales std::cout y std::cin (std = funcionalidad estandar) (std::cout salida estandar, la terminal)(std::cin entrada estandar, la terminal)
#include <string> //cadena de caracteres estandar
#include <vector> //contenedor secuencial de datos recomendado en c++
#include "pel_print.hpp" // O si añadimos el documento descargado del profesor pel_print.hpp
//----------------------------------------
/*
auto do_something() -> void{ //void porque no retorna nada

    auto f = float{7.5f};
    auto i = int{14};

}

auto main() -> int{// a la derecha se pone el tipo que retorna
    
    //creamos las variables
    auto n = int{1};// variable entero o podemos poner tambien int n = 1
    auto d = double{9.8}; //variable decimal
    auto c = char{'z'}; // variable caracter

    do_something();//llamamos a una funcion y genera lo que este dentro

    //cuando termine do_something


    //return 0; // se suele tener que poner esto o se da por entendido en funciones int para decir que ha salido con exito
}*/

//----------------------------------------
/*
class S{ //creamos una clase
//todo lo que esta dentro de una clase es privado por defecto
    int id;

public: //si pongo public, todo lo que ponga abajo sera público
    //creamos el contructor
    S(int idx){
        id = idx;//con esto ya puedo crear tantos objetos de la clase s que yo quiera y puede almacenar un entero
        std::cout << "creando objeto #" << idx << '\n';
    }

    //DEFINIMOS AL DESTRUCTOR, con el nombre de la clase y solo puede haber 1, automaticamente el proceso lo llama
    ~S(){
        //aqui ponemos lo que queramos hacer antes de destruir los objetos, en una estructura FIFO
        std::cout << "destruyendo el objeto #" << id << '\n'; //justo antes de que l subobjeto id sea destruido, imprime por pantalla el objeto que se esta destruyendo
    }

};


auto main() -> int{
    /*
    auto s1 = S{1};
    auto s2 = S{2};
    auto s3 = S{3};
    */
    //auto s1 = S{1};{
       // auto s2 = S{2};
       // auto s3 = S{3};
    //}    
    //auto s4 = S{4};
    //para retornar el estado del exito
    //return EXIT_SUCCESS;

//}


//----------------------------------------
//pregunta de examen: ¿limitaciones fundamentales de la pila de usuario? 1) Conocer el tipo de variable que estoy enviando 2)Tamaño del objeto que estoy almacenando 3)memoria reducida para la liberación y asignación de variables
//----------------------------------------
//ejemplo: preguntar al usuario cuantos nombres quiere introducir (ARRAY DINÁMICO) y cuando quiera imprima
//EN ESTO CONSISTE LA TÉCNICA RAII
/*
auto main() -> int{
    
   //creamos una variable local de tipo vector
   auto names = std::vector<std::string>{};//entre <> ponemos lo que vamos a almacenar y llamamos al constructor por defecto, inicializa un array dinamico de strings vacio, el vector ya tiene un destructor implementado

   auto nm = std::string{}; //string vacio donde guardaremos los nombres
   std::cout << "Introduce un nombre: ";
   //creamos un bucle while
   while (std::getline(std::cin, nm)){ //getline: es para capturar la cadena de caracteres indicando donde (terminal) y donde queremos almacenarlo

        names.push_back(nm); //introduce al fondo el string del array y asi hasta que nos cansemos y pulsemos CRTL+Z para finalizar
        std::cout << "Introduce otro nombre o finaliza con CTRL + Z: ";
   }
   //imprimimos por cada nombre que encuentre en el array (BUCLE BASADO EN RANGOS)
   for(std::string name : names){ // a la derecha ponemos el vector y a la izq el tipo de dato que vamos a iterar dandole un nombre
        std::cout << name << '\n';
   }
   //al final del programa de destruira los string y el vector, en orden contrario al que se crearon
}
*/

//-- REFERENCIAS --
// {} modo para formatear un string indicando donde van los result de las variables
/*
auto main() -> int{

    auto age = int{26};
    auto name = std::string{"Alberto"};
    //std::cout << std::format("nombre: {}, edad: {}", name, age);
    //con el include de  pel_print.hpp :
    pel::println("nombre: {}, edad: {}", name, age);
}
*/
/*
auto incrementar_una_unidad(int n) -> void{// funcion que recibe un entero, y no retorna valor (es void)
    ++n;
}
auto incrementar_una_unidad1(int& n) -> void{// funcion que recibe un entero, haciendo referencia al entero que pase el programador, siendo este un alias y devuelve el num + 1
    ++n;
}
auto incrementar_una_unidad2(int n) -> int{// funcion que recibe un entero, y devuelve el valor aumentado en 1
    ++n;
    return n;
}

auto main() -> int{

    auto i = int{1};
    //auto j = i; //variable independiente
    //auto& j = i; //si le añadimos & en el auto, es que j es una referencia, un alias a i, pero es el mismo, las modificaciones que hagamos se aplican a los dos
    //++j; //sumamos 1
    //pel::println("i = {}, j = {}", i , j);
    //---
    incrementar_una_unidad1(i);
    //i = incrementar_una_unidad2(i);
    //---
    pel::println("i = {}", i);   

}
*/
/*
auto add_z(std::string str) -> void {//concatena al string el texto que llamemos a la funcion
    str += "z";
}
auto add_z1(std::string& str) -> void {//concatena al string el texto que llamemos a la funcion si ponemos el & ya si funciona
    str += "z";
}
auto main() -> int{
    auto text = std::string{"Hola Mundo"};
    auto const text = std::string{"Hola Mundo"}; //definimos una variable constante, que no cambia el valor
    add_z1(text);
    pel::println("Text = {}, text");
}*/

//-- PUNTEROS --
//variables que almacenan direcciones de memoria
/*
auto main() -> int{
    //variable que almacena la direccion de meroria de otra variable 8bytes 64 bits 4bytes en 32bits
    auto i = int{1};
    //puntero a ese entero
    int* p = &i;//guardar en p la direccion de memoria de la variable i

    //imprimimos p y nos da la direccion
    std::cout << p;
    //con un mensaje mas formateado
    pel::println("Cuanto ocupa en memoria i = {} bytes", sizeof(i));
    pel::println("Cuanto ocupa en memoria p = {} bytes", sizeof(p));

    auto d = double{7.8};
    double* q = &d;

    pel::println("Cuanto ocupa en memoria d = {} bytes", sizeof(d));
    pel::println("Cuanto ocupa en memoria q = {} bytes", sizeof(q));

    //imprimir por pantalla el valor i pero utilizando el puntero que lo esta almacenando
    pel::println("i = {}",*p);// el* es para sacar lo que apunta, el valor que apunta el puntero

    //incrementar el valor de i en 2 unidades pero atraves del puntero
    *p = *p + 2;
    pel::println("i = {}",*p);

}*/
/*
//utilizando un agregado de datos struct cuyas variables son públicas
struct Student{ //tres notas para cada estudiante
    std::string name;
    double grade1;
    double grade2;
    double grade3;

    //funcion publica para calcular la nota media
    auto average() -> double{
        return(grade1 + grade2 + grade3)/3.0;
    }
    
};

auto main() -> int{
    auto s = Student("Alberto", 9.8, 7.5, 9.2);//objeto de tipo estudiante
    pel::println("name = {} | nota media = {:.2f}", s.name, s.average()); // poniendo esto {:.2f} es para que nos salga solo 2 decimales

    //variable para imprimir la direccion de memoria de ese estudiante
    Student* a = &s;//puntero a estudiante
    std::cout << a;

    //para modificar la nota del segundo examen
    s.grade2 = 9.2;
    pel::println("name = {} | nota media modificada = {:.2f}", s.name, s.average());

    //para modificar la nota del segundo examen, pero utilizando el puntero
    (*a).grade2 = 10;
    pel::println("name = {} | nota media con puntero = {:.2f}", (*a).name, (*a).average());

    //otra forma de trabajar con punteros también seria utilizando la flecha
    a->grade2 = 5;
    pel::println("name = {} | nota media cin flecha = {:.2f}", a->name, a->average());


}*/
//utilñizando un puntero a entero primero con una referencia y luego con un entero
//REFERENCIA
/*
auto incrementar_una_unidad (int& n) -> void{
    ++n;
}
*/
/*
//PUNTERO
auto incrementar_una_unidad (int* p) -> void{
    ++(*p);
}
*/
/*

auto main() -> int{
    auto i = int{1};
    incrementar_una_unidad(i);
    pel::println("entero = {}",i);

}
*/