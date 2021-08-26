#include <bits/stdc++.h>
using namespace std;

#ifdef __APPLE__
const string clear = "clear";
const string reset = "\033[0m", blue = "\033[1;34m", purple = "\033[3;95m", red = "\033[1;31m", green = "\033[1;32m";
#else
const string clear = "cls";
const string reset = "", blue = "", purple = "", red = "", green = "";
#endif

string lexema(char token) {
  if ('0' <= token && token <= '9') {
    return "<digito>";
  } else if (('A' <= token && token <= 'Z') || ('a' <= token && token <= 'z') || (token == '_')) {
    return "<letra>";
  } else if (token == '+' || token == '-' || token == '*' || token == '/' || token == '=' || token == '<' || token == '>') {
    return "<operador>";
  } else if (token == '.') {
    return "<punto>";
  }
  return"<error>";
}

int funcion(int estado, char entrada) {
  /**
   * Función f en un autómata para obtener el estado siguiente.
   * @param estado - Estado Actual del Automata.
   * @param entrada - Caracter de entrada.
   * @return Estado Siguiente.
   */

  string lex = lexema(entrada);

  // Transiciones
  if (estado == 0) {
    if (lex == "<letra>") {
      estado = 1;
    } else if (lex == "<digito>") {
      estado = 2;
    } else if (lex == "<operador>") {
      if (entrada == '+' || entrada == '-') {
        estado = 3;
      } else if (entrada == '/' || entrada == '*') {
        estado = 12;
      } else if (entrada == '<' || entrada == '>') {
        estado = 13;
      } else {
        estado = 16;
      }
    } else if (lex == "<punto>") {
      estado = 4;
    } else {
      estado = 100;
    }
  } else if (estado == 1) {
    if (lex == "<letra>" || lex == "<digito>") {
      estado = 1;
    } else {
      estado = 101;
    }
  } else if (estado == 2) {
    if (lex == "<digito>") {
      estado = 2;
    } else if (lex == "<punto>") {
      estado = 4;
    } else if (lex == "<letra>" && (entrada == 'e' || entrada == 'E')) {
      estado = 9;
    } else {
      estado = 102;
    }
  } else if (estado == 3) {
    if (lex == "<digito>") {
      estado = 6;
    } else if (lex == "<operador>") {
      if (entrada == '=') {
        estado = 14;
      } else {
        estado = 103;
      }
    } else {
      estado = 103;
    }
  } else if (estado == 4) {
    if (lex == "<digito>") {
      estado = 5;
    } else {
      estado = 104;
    }
  } else if (estado == 5) {
    if (lex == "<digito>") {
      estado = 5;
    } else if (lex == "<letra>" && (entrada == 'e' || entrada == 'E')) {
      estado = 9;
    } else {
      estado = 105;
    }
  } else if (estado == 6) {
    if (lex == "<digito>") {
      estado = 6;
    } else if (lex == "<punto>") {
      estado = 7;
    } else if (lex == "<letra>" && (entrada == 'e' || entrada == 'E')) {
      estado = 9;
    } else {
      estado = 106;
    }
  } else if (estado == 7) {
    if (lex == "<digito>") {
      estado = 8;
    } else {
      estado = 107;
    }
  } else if (estado == 8) {
    if (lex == "<digito>") {
      estado = 8;
    } else if (lex == "<letra>" && (entrada == 'e' || entrada == 'E')) {
      estado = 9;
    } else {
      estado = 108;
    }
  } else if (estado == 9) {
    if (lex == "<digito>") {
      estado = 11;
    } else if (lex == "<operador>") {
      if (entrada == '+' || entrada == '-') {
        estado = 10;
      } else {
        estado = 109;
      }
    } else {
      estado = 109;
    }
  } else if (estado == 10) {
    if (lex == "<digito>") {
      estado = 11;
    } else {
      estado = 110;
    }
  } else if (estado == 11) {
    if (lex == "<digito>") {
      estado = 11;
    } else {
      estado = 111;
    }
  } else if (estado == 12) {
    if (lex == "<operador>") {
      if (entrada == '=') {
        estado = 14;
      } else {
        estado = 112;
      }
    } else {
      estado = 112;
    }
  } else if (estado == 13) {
    if (lex == "<operador>") {
      if (entrada == '=') {
        estado = 15;
      } else {
        estado = 113;
      }
    } else {
      estado = 113;
    }
  } else if (estado == 14) {
    estado = 114;
  } else if (estado == 15) {
    estado = 115;
  } else if (estado == 16) {
    if (lex == "<operador>") {
      if (entrada == '=') {
        estado = 17;
      } else {
        estado = 116;
      }
    } else {
      estado = 116;
    }
  } else if (estado == 17) {
    estado = 117;
  }

  return estado;
}

bool esPalabraReservada(const string &cadena) {
  const static vector<string> palabrasReservadas = {
      "auto",   "const",    "double",   "float",    "int",     "short",
      "struct", "unsigned", "break",    "continue", "else",    "for",
      "long",   "signed",   "switch",   "void",     "case",    "default",
      "enum",   "goto",     "register", "sizeof",   "typedef", "volatile",
      "char",   "do",       "extern",   "if",       "return",  "static",
      "union",  "while"};

  for (auto palabra : palabrasReservadas)
    if (cadena == palabra)
      return true;

  return false;
}

void analizador() {
  const static vector<string> errores = {
    "[a-z|A-Z|_|0-9|.|+,-,*,/,<,>,=]", "[a-z|A-Z|_|0-9]", "[0-9|.|e,E]",
    "[0-9|=]", "[0-9]", "[0-9|e,E]", "[0-9|.|e,E]", "[0-9]", "[0-9|e,E]",
    "[0-9|+,-]", "[0-9]", "[0-9]", "[=]", "[=]", "[]", "[]", "[=]", "[]"};

  cout << blue << "Ingresa una cadena-> " << reset << '\n';

  string cadena;
  cin.ignore();
  getline(cin, cadena);

  if (esPalabraReservada(cadena)) {
    // Es una palabra reservada todo está bien
    cout << green << "Palabra " << cadena << " reservada de C valida\n";
  } else {
    // Rip, veamos qué error fue
    int i = 0, estado = 0;

    while (i < cadena.size()) {
      estado = funcion(estado, cadena[i]);
      if (estado >= 100) {  // Estados de error
        cout << red << "ERROR: Se esperaba " << errores[estado - 100] << " en la posición " << i + 1 << " y se recibio '" << cadena[i] << "'\n" << reset;
        break;
      }
      i++;
    }

    if (estado < 100) {
      // Estado de aceptación
      cout << green;
      if (estado == 1) {
        cout << "Identificador valido\n";
      } else if (estado == 2) {
        cout << "Entero sin signo valido\n";
      } else if (estado == 3 || estado == 12) {
        cout << "Operador aritmetico valido\n";
      } else if (estado == 5) {
        cout << "Flotante sin signo valido\n";
      } else if (estado == 6) {
        cout << "Entero con signo valido\n";
      } else if (estado == 8) {
        cout << "Flotante con signo valido\n";
      } else if (estado == 11) {
        cout << "Exponencial valido\n";
      } else if (estado == 13 || estado == 15 || estado == 17) {
        cout << "Operador de comparacion valido\n";
      } else if (estado == 14 || estado == 16) {
        cout << "Operador de asignacion valido\n";
      } else {
        cout << red << "ERROR: Se esperaba " << errores[estado] << " en la última posicion y no se recibio nada\n";
      }
      cout << reset;
    }
  }

  cout << "";
}

int main() {
  int op = 0;
  enum { ANALIZAR = 1, INFORMACION, SALIR};

  while (op != 3) {
    system(clear.c_str());
    cout << blue << "***************************************************\n";
    cout << "*           Analizador Lexico                     *\n";
    cout << "***************************************************\n\n";
    cout << purple << "1) Analizar Cadenas\n";
    cout << "2) Informacion sobre el Analizador\n";
    cout << "3) Salir\n";
    cout << "Seleccion -> " << reset;
    cin >> op;

    switch (op) {
      case ANALIZAR: {
        analizador();
        break;
      }

      case INFORMACION: {
        system(clear.c_str());
        cout << blue << "Los siguientes tipos de cadenas son aceptadas\n\n";
        cout << purple << "* Identificadores\n";
        cout << "* Enteros con signo y sin signo\n";
        cout << "* Flotantes con signo y sin signo\n";
        cout << "* Exponenciales\n";
        cout << "* Palabras reservadas de C\n";
        cout << "* Operadores aritmeticos de C\n";
        cout << "* Operadores logicos de C\n";
        cout << "* Operadores de asignacion de C (Excepto ++ y --)\n\n";

        cout << blue << "Analizador Lexico implementado por:\n" << reset;
        const static vector<string> nombres = {
            "Abraham Baltazar Murillo Sandoval", "Jesus Ernesto Salas Herrera",
            "Jesus Uriel Guzman Mendoza"};
        for (auto nombre : nombres)
          cout << purple << "* " << nombre << "\n" << reset;
        break;
      }

      case SALIR: {
        cout << "Hasta luego...\n";
        break;
      }

      default: {
        cout << "Opción Invalida\n";
        cout << "Vuelve a intentarlo\n";
        break;
      }
    }

    cout << blue << "\nPresiona un caracter y <enter> para continuar...\n" << reset;
    char continuar;
    cin >> continuar;

  }

  return 0;
}
