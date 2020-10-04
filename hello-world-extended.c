/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * hello-world-extended.c
 * 10/03/2020 (mm/dd/yyyy)
 * by Jon Foster
 * jonfos@devjonfos.net
 * 
 * License: CC BY-NC-SA 
 *    https://creativecommons.org/licenses/by-nc-sa/4.0/
 *    Attribution-NonCommercial-ShareAlike
 * 
 * Extending the hello-world gtk example with a dialog
 * printing the dialog response on standard output
 * 
 * https://www.gtk.org/docs/getting-started/hello-world/
 * 
 * Notice the internalization header for 
 * the _("_OK") , _("_Cancel") macros
 * 
 * Also, the callback function for a dialog's response signal is
 * void user_function (GtkDialog *dialog, int response_id, gpointer user_data)
 * https://developer.gnome.org/gtk3/stable/GtkDialog.html#GtkDialog-response
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <glib/gi18n.h>
#include <gtk/gtk.h>

// Print a simple message on the standard output
static void
print_message (GtkDialog *dialog, int response_id, gpointer user_data)
{
  GtkResponseType response_enum = response_id;
  gchar *response_message;

  switch (response_enum)
  {
    case GTK_RESPONSE_NONE :
     response_message = "none";
     break;

    case GTK_RESPONSE_REJECT :
     response_message = "reject";
     break;

    case GTK_RESPONSE_ACCEPT :
     response_message = "accept";
     break;

    case GTK_RESPONSE_DELETE_EVENT :
     response_message = "delete";
     break;

    case GTK_RESPONSE_OK :
     response_message = "ok";
     break;

    case GTK_RESPONSE_CANCEL :
     response_message = "cancel";
     break;

    case GTK_RESPONSE_CLOSE :
     response_message = "close";
     break;

    case GTK_RESPONSE_YES :
     response_message = "yes";
     break;

    case GTK_RESPONSE_NO :
     response_message = "no";
     break;

	  case GTK_RESPONSE_APPLY :
     response_message = "apply";
     break;

    case GTK_RESPONSE_HELP :
     response_message = "help";
     break;

    default :
     response_message = "default";
  }
	
  g_print ("%s: %s = %d\n", (gchar *)user_data, response_message, response_id);
}

// Function to open a dialog box with a message
static void
quick_message (GtkWindow *parent, gchar *message)
{
 GtkWidget *dialog, *label, *content_area;
 GtkDialogFlags flags;
 gchar *response_message = "Button clicked";

 // Create the widgets
 flags = GTK_DIALOG_DESTROY_WITH_PARENT | GTK_DIALOG_MODAL;
 dialog = gtk_dialog_new_with_buttons ("Message",
                                       parent,
                                       flags,
                                      _("_OK"),
                                      GTK_RESPONSE_ACCEPT,
                                      _("_Cancel"),
                                      GTK_RESPONSE_CANCEL,
                                       NULL);
 content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
 label = gtk_label_new (message);

 // Feedback from dialog buttons
 g_signal_connect (dialog, "response", G_CALLBACK (print_message), response_message);
 
 // Ensure that the dialog box is destroyed when the user responds
 g_signal_connect_swapped (dialog, "response", G_CALLBACK (gtk_widget_destroy), dialog);

 // Add the label, and show everything we’ve added
 gtk_container_add (GTK_CONTAINER (content_area), label);
 gtk_widget_show_all (dialog);
}

static void
print_hello (GtkWidget *widget,
             gpointer   data)
{
  g_print ("Hello World!\n");
  quick_message(GTK_WINDOW(data), "A quick message here in a dialog.");
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *button_box;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);

  button = gtk_button_new_with_label ("Hello World");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), window);
  gtk_container_add (GTK_CONTAINER (button_box), button);

  gtk_widget_show_all (window);
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

