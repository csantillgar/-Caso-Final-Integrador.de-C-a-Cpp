#include<iostream>
#include<string>
#include<cstdio>
using namespace std;

struct ColorConsole {
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto fg_white = "\033[47m";
};

struct ConsoleBox
{
    void new_text() {/* Implementación para limpiar o preparar la consola para un nuevo texto */}
    void set_text(const string &text) { cout << text << endl; }
};

ConsoleBox *consoleBox = new ConsoleBox;
void load_script(const char* filename, bool show_script = false)
{
    string script;
    FILE* f = nullptr;
    try
    {
        f = fopen(filename, "rb");
        if (!f)
        {
            cerr << "error de apertura de " << filename << endl;
            return;
        }

        int c;
        char buf[4001];
        while ((c = fread(buf, 1, 4000, f)) > 0)
        {
            buf[c] = 0;
            script.append(buf);
        }
        fclose(f);
        f = nullptr;

        if (show_script)
        {
            cout << ColorConsole::fg_blue << ColorConsole::fg_white;
            cout << script << endl;
        }
        consoleBox->new_text();
        consoleBox->set_text(script);
    }
    catch (const std::exception &e)
    {
        cerr << "Error durante la lectura del archivo: " << e.what() << endl;
        if(f)
            fclose(f);
    }
}

void load_script()
{
    char filename[500];
    printf("Archivo: ");
    scanf("%499s", filename);
    load_script(filename, true);
    try
    {
        load_script(filename, true);
    }
    catch (const std::exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}

int main()
{
    load_script();  // Solicita al usuario un archivo y muestra su contenido
    return 0;
};