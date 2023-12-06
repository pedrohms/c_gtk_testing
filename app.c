#include "stdio.h"
#include <gtk/gtk.h>
#include <gtk/gtkcenterlayout.h>

static void onclick(GtkApplication *app, gpointer *g_pointer);
static void activate(GtkApplication *app, gpointer user_data);

GtkWidget *window;
GtkWidget *verticalBox;
GtkWidget *spacingBoxLeft, *spacingBoxRight;
GtkWidget *horizontalBox;
GtkWidget *searchButton;
GtkWidget *confirmButton;

static void activate(GtkApplication *app, gpointer user_data) {

  window = gtk_application_window_new(app);
  verticalBox = GTK_WIDGET(gtk_box_new(GTK_ORIENTATION_VERTICAL, 10));
  horizontalBox = GTK_WIDGET(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10));
  spacingBoxLeft = GTK_WIDGET(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10));
  spacingBoxRight = GTK_WIDGET(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10));

  searchButton = gtk_button_new_with_label("search");
  confirmButton = gtk_button_new_with_label("Ok");

  gtk_box_prepend(GTK_BOX(verticalBox), searchButton);
  gtk_box_append(GTK_BOX(verticalBox), confirmButton);

  gtk_box_set_baseline_position(GTK_BOX(verticalBox),
                                GTK_BASELINE_POSITION_CENTER);
  gtk_box_set_baseline_position(GTK_BOX(horizontalBox),
                                GTK_BASELINE_POSITION_CENTER);
  gtk_box_set_baseline_position(GTK_BOX(spacingBoxRight),
                                GTK_BASELINE_POSITION_CENTER);
  gtk_box_set_baseline_position(GTK_BOX(spacingBoxLeft),
                                GTK_BASELINE_POSITION_CENTER);

  gtk_window_set_title(GTK_WINDOW(window), "Window");
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

  gtk_box_prepend(GTK_BOX(horizontalBox), spacingBoxLeft);
  gtk_box_append(GTK_BOX(horizontalBox), verticalBox);
  gtk_box_prepend(GTK_BOX(horizontalBox), spacingBoxRight);

  gtk_window_set_child(GTK_WINDOW(window), horizontalBox);

  g_signal_connect(confirmButton, "clicked", G_CALLBACK(onclick), NULL);

  gtk_window_present(GTK_WINDOW(window));
}

static void onclick(GtkApplication *app, gpointer *g_pointer) {
  gtk_window_close(GTK_WINDOW(window));
}

int main(int argc, char **argv) {

  GtkApplication *app;

  int status;

  app = gtk_application_new("org.gtk.teste", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);

  g_object_unref(app);

  return status;
}
