#include <gtk/gtk.h>
#include <gtkmm.h>

#include <list>
#include <string>

#include <stdlib.h>
#include <iostream>
#include <string>

#include "configdata.h"

#define OK 1
#define CANCEL 2

using sigc::bind;
using sigc::slot;

using namespace std;

class GUI : public Gtk::Window
{
    Gtk::HBox box1, box2, box3, box4, box5;
    Gtk::VBox box6;
    Gtk::Label lCommand, lQuality, lFont, lCpi;
    Gtk::Entry tCommand;
    Gtk::ComboBoxText cQuality, cFont, cCpi;
    Gtk::Button bOk, bCancel;

public:
    GUI();

    void callback(int data);

    gint delete_event_impl(GdkEventAny*) { 
        Gtk::Main::quit(); 
        return 0; 
    }
};

GUI::GUI() :
    box1(true, 0),
    box2(true, 0),
    box3(true, 0),
    box4(true, 0),
    box5(true, 0),
    box6(false, 10),
    lCommand("Printing Command: "),
    lQuality("Quality: "),
    lFont("Font (only NLQ): "),
    lCpi("Character Width: "),
    tCommand(),
    cQuality(),
    cFont(),
    cCpi(),
    bOk("Ok"),
    bCancel("Cancel")
{
    set_title("epson_setup (c) 2003 Markus Heinz");

    set_border_width(10);

    tCommand.set_text("lpr");

    cQuality.append("Draft");
    cQuality.append("NLQ");
    cQuality.set_active(0);

    cFont.append("Roman");
    cFont.append("Sans Serif");
    cFont.set_active(0);

    cCpi.append("10 cpi");
    cCpi.append("12 cpi");
    cCpi.set_active(0);

    box6.pack_start(box1);
    box6.pack_start(box2);
    box6.pack_start(box3);
    box6.pack_start(box4);
    box6.pack_start(box5);

    add(box6);

    box1.pack_start(lCommand);
    box1.pack_start(tCommand);

    box2.pack_start(lQuality);
    box2.pack_start(cQuality);

    box3.pack_start(lFont);
    box3.pack_start(cFont);

    box4.pack_start(lCpi);
    box4.pack_start(cCpi);

    bOk.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(this, &GUI::callback), OK));
    box5.pack_start(bOk);
    bCancel.signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(this, &GUI::callback), CANCEL));
    box5.pack_start(bCancel);

    show_all();
}

void GUI::callback(int data)
{
    int q, t, c;
    string s("echo -n ");

    if (cQuality.get_active_text() == "Draft")
        q = 0;
    else 
        q = 1;

    if (cFont.get_active_text() == "Roman")
        t = 0;
    else 
        t = 1;

    if (cCpi.get_active_text() == "10 cpi")
        c = 0;
    else 
        c = 1;

    ConfigData cd(tCommand.get_text().raw(), q, t, c);
    s += cd.getData();
    s += " | ";
    s += cd.getCommand();

    if (data == OK) { 
        int r = system(s.c_str());
        std::cout << "Lpr exit code: " << r << endl;
    }

    Gtk::Main::quit();
}

int main (int argc, char *argv[])
{
    Gtk::Main kit(argc, argv);

    GUI gui;

    kit.run();
    return 0;
}
