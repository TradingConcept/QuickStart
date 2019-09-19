#include "Dog.h"

using namespace std;

Dog::Dog(int age, string name)
{

    this->age = age;
    this->name = name;

    cout << "Dog " << this->name << " created" << std::endl;
}

Dog::Dog(string name) : Dog(0, name)
{
}

Dog::~Dog()
{
    cout << "Dog " << this->name << " destroyed" << std::endl;
}

void Dog::bark()
{
    cout << "Dog " << this->name << " rules!" << std::endl;
}

void Dog::Run()
{

    Dog c0(10, "oso");
    c0.bark();

    Dog c1 = {17, "gris"};
    c1.bark();

    Dog c2{17, "perro"};
    c2.bark();
}

void Dog::RunTests()
{

    auto p99 = new Dog("99");
    p99->bark(); // nunca se destruye, error deluiberado

    auto p0 = Dog("Coquis");
    p0.bark();

    std::shared_ptr<Dog> p1(new Dog("Oso")); // no puedo ponerla autom�tica porque no la reconoce
    p1->bark();

    auto myLambdaConParametroPorReferencia = [](const shared_ptr<Dog> &p1) {
        auto p1a = p1; // asignamos a nueva variable, se incrementa el contador
        p1a->bark();
        // cuando es por referencia, el shared_pointer no incrementa los usuarios, pues no es una asignaci�n
        cout << "En lambda parametro referencia " << p1.use_count() << std::endl;
    };

    auto myLambdaConParametroDirecto = [](const shared_ptr<Dog> p1) {
        auto p1a = p1; // asignamos a nueva variable, se incrementa el contador
        p1a->bark();
        // cuando es por par�metro directo, el shared_pointer si incrementa los usuarios pues a fin de cuentas, es una asignaci�n
        cout << "En lambda parametro directo " << p1.use_count() << std::endl;
    };

    myLambdaConParametroPorReferencia(p1);
    myLambdaConParametroDirecto(p1);
    cout << "Fuera de lambda " << p1.use_count() << std::endl;
    ; // tengo dos referenciadores, pero se va a morir apenas termine este contexto

    auto p2 = make_shared<Dog>("Perro"); // este es el preferido
    p2->bark();

    // hay otras moner�as como custom destructors, y raw pointers, etc...
    // https://www.youtube.com/watch?v=n10ERmH8bYk
}
