/* gtask-example-window.c
 *
 * Copyright (C) 2017 albfan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtk/gtk.h>
#include "gtask-example-config.h"
#include "gtask-example-window.h"

struct _GtaskExampleWindow
{
  GtkWindow     parent_instance;
  GtkHeaderBar *header_bar;
  GtkLabel     *label;
  GtkButton    *button;
};

G_DEFINE_TYPE (GtaskExampleWindow, gtask_example_window, GTK_TYPE_APPLICATION_WINDOW)

static void
say_hurra (GTask *task,
               gpointer source_obj,
               gpointer task_data,
               GCancellable *cancellable)
{


  while(1)
    {
      printf("hurrah!\n");
      /* Break if GCancellable.cancel() was called */
      if (g_cancellable_is_cancelled (cancellable))
      {
        g_task_return_new_error (task,
                                 G_IO_ERROR, G_IO_ERROR_CANCELLED,
                                 "Task cancelled");
          return;
      }
    }

  /* The task has finished */
  g_task_return_boolean (task, TRUE);
}

void
say_hurra_finish (GObject *source_object,
                        GAsyncResult *res,
                        gpointer user_data)
{
  //TODO: What to do here
}

void display(GtkButton* b, gpointer data)
{
  GCancellable* cancellable =  g_cancellable_new();
  gpointer p = b;
  GTask *task = g_task_new (p, cancellable, say_hurra_finish, NULL);
  g_task_run_in_thread (task, say_hurra);
  g_object_unref (task);
}

static void
gtask_example_window_class_init (GtaskExampleWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/Gtask-Example/gtask-example-window.ui");
  gtk_widget_class_bind_template_child (widget_class, GtaskExampleWindow, label);
  gtk_widget_class_bind_template_child (widget_class, GtaskExampleWindow, button);
}

static void
gtask_example_window_init (GtaskExampleWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
  g_signal_connect (self->button, "clicked", G_CALLBACK (display), NULL);

}

