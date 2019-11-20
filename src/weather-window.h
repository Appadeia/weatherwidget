/* weather-window.h
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

#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

struct _WeatherWindow
{
  GtkApplicationWindow  parent_instance;

  /* Template widgets */
  GtkHeaderBar        *header_bar;
  GtkLabel            *city_label;
  GtkLabel            *country_label;
  GtkLabel            *temp_label;
  GtkImage            *weather_icon;
  GtkBox              *label_boxy;
};

#define WEATHER_TYPE_WINDOW (weather_window_get_type())

G_DECLARE_FINAL_TYPE (WeatherWindow, weather_window, WEATHER, WINDOW, GtkApplicationWindow)

#define WEATHER_WINDOW(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), WEATHER_TYPE_WINDOW, WeatherWindow))

G_END_DECLS
