/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * example-3-extended.c
 * 10/05/2020 (mm/dd/yyyy)
 * by Jon Foster
 * jonfos@devjonfos.net
 * 
 * License: CC BY-NC-SA 
 *    https://creativecommons.org/licenses/by-nc-sa/4.0/
 *    Attribution-NonCommercial-ShareAlike
 * 
 * Extending the example-3.c gtk example with multiple
 * buttons, printing the name on standard output
 * 
 * https://developer.gnome.org/gtk3/stable/ch01s03.html
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <gtk/gtk.h>

static void
print_button_name (GtkWidget *widget,
                   gpointer   data)
{
  g_print ("%s\n", (gchar *)data);
}

int
main (int   argc,
      char *argv[])
{
  GtkBuilder *builder;
  GObject *window;
  GObject *button;
  GError *error = NULL;
  gchar *button_labels[6] = {"button1","button2","button3","button4","button5","button6"};

  gtk_init (&argc, &argv);

  /* Construct a GtkBuilder instance and load our UI description */
  builder = gtk_builder_new ();
  if (gtk_builder_add_from_file (builder, "builder-example3-extended.ui", &error) == 0)
    {
      g_printerr ("Error loading file: %s\n", error->message);
      g_clear_error (&error);
      return 1;
    }

  /* Connect signal handlers to the constructed widgets. */
  window = gtk_builder_get_object (builder, "window");
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  button = gtk_builder_get_object (builder, "button1");
  g_signal_connect (button, "clicked", G_CALLBACK (print_button_name), button_labels[0]);

  button = gtk_builder_get_object (builder, "button2");
  g_signal_connect (button, "clicked", G_CALLBACK (print_button_name), button_labels[1]);

  button = gtk_builder_get_object (builder, "button3");
  g_signal_connect (button, "clicked", G_CALLBACK (print_button_name), button_labels[2]);

  button = gtk_builder_get_object (builder, "button4");
  g_signal_connect (button, "clicked", G_CALLBACK (print_button_name), button_labels[3]);

  button = gtk_builder_get_object (builder, "button5");
  g_signal_connect (button, "clicked", G_CALLBACK (print_button_name), button_labels[4]);

  button = gtk_builder_get_object (builder, "button6");
  g_signal_connect (button, "clicked", G_CALLBACK (print_button_name), button_labels[5]);

  button = gtk_builder_get_object (builder, "quit1");
  g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);

  button = gtk_builder_get_object (builder, "quit2");
  g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);

  button = gtk_builder_get_object (builder, "quit3");
  g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);

  gtk_main ();

  return 0;
}
