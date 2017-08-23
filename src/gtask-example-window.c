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

gboolean on_idle()
{
  printf("hurrah!\n");
  return G_SOURCE_CONTINUE;
  //TODO: Detect window close to stop this
  //return G_SOURCE_REMOVE;
}

void display(GtkButton * b, gpointer data)
{
  g_idle_add (on_idle, NULL);
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

