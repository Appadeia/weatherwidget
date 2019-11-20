/* weather-window.c
 *
 * Copyright 2019 Carson Black
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

#include "weather-config.h"
#include "weather-window.h"

G_DEFINE_TYPE (WeatherWindow, weather_window, GTK_TYPE_APPLICATION_WINDOW)

static void
weather_window_class_init (WeatherWindowClass *klass)
{
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  gtk_widget_class_set_template_from_resource (widget_class, "/me/appadeia/WeatherWidget/weather-window.ui");
  gtk_widget_class_bind_template_child (widget_class, WeatherWindow, header_bar);
  gtk_widget_class_bind_template_child (widget_class, WeatherWindow, city_label);
  gtk_widget_class_bind_template_child (widget_class, WeatherWindow, country_label);
  gtk_widget_class_bind_template_child (widget_class, WeatherWindow, temp_label);
  gtk_widget_class_bind_template_child (widget_class, WeatherWindow, weather_icon);
  gtk_widget_class_bind_template_child (widget_class, WeatherWindow, label_boxy);
}

static void
weather_window_init (WeatherWindow *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}
