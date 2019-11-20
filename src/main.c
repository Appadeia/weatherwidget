/* main.c
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

#include <glib/gi18n.h>
#include <libgweather-3.0/libgweather/gweather.h>
#include <gdk/gdkx.h>

#include "weather-config.h"
#include "weather-window.h"

GWeatherLocationEntry *entry;
GWeatherLocation *loc = NULL;
GWeatherInfo *info = NULL;
WeatherWindow *winny;

static gboolean
poll() {
	if(info == NULL)
		return TRUE;
	
	gweather_info_update(info);
	return TRUE;
}

static void
update() {
	gtk_image_set_from_icon_name(winny->weather_icon, gweather_info_get_symbolic_icon_name(info), GTK_ICON_SIZE_BUTTON);
	gtk_label_set_text(winny->temp_label, gweather_info_get_temp(info));
}

static void
entry_connect() {
	if (gweather_location_entry_get_location(entry) != NULL) {
		loc = gweather_location_entry_get_location(entry);
		gtk_label_set_text(winny->city_label, gweather_location_get_city_name(loc));
		gtk_label_set_text(winny->country_label, gweather_location_get_country_name(loc));
		info = gweather_info_new(loc);
		g_signal_connect(info, "updated", update, NULL);
		
		poll();
	}
}

static void
on_activate (GtkApplication *app)
{
	GtkWindow *window;

	/* It's good practice to check your parameters at the beginning of the
	 * function. It helps catch errors early and in development instead of
	 * by your users.
	 */
	g_assert (GTK_IS_APPLICATION (app));

  	g_autoptr(GtkCssProvider) prov = gtk_css_provider_new();
  	gtk_css_provider_load_from_resource (prov, "/me/appadeia/WeatherWidget/app.css");
  	gtk_style_context_add_provider_for_screen (
  	  gdk_screen_get_default(),
  	  prov,
  	  GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
  	);

	g_autoptr(GtkSettings) settings = gtk_settings_get_default();
	g_object_set(settings, "gtk-theme-name", "Adwaita", "gtk-icon-theme-name", "Adwaita", "gtk-font-name", "Cantarell 11", "gtk-decoration-layout", ":close", "gtk-application-prefer-dark-theme", TRUE, NULL);

	/* Get the current window or create one if necessary. */
	window = gtk_application_get_active_window (app);
	if (window == NULL)
		window = g_object_new (WEATHER_TYPE_WINDOW,
		                       "application", app,
		                       "default-width", 600,
		                       "default-height", 300,
		                       NULL);

	winny = WEATHER_WINDOW(window);

	entry = gweather_location_entry_new(NULL);
	
	gtk_box_pack_start(winny->label_boxy, entry, FALSE, FALSE, 0);

	gtk_widget_show(GTK_WIDGET(entry));
	g_signal_connect(entry, "activate", (GCallback) entry_connect, NULL);

	g_timeout_add_seconds(30, (GSourceFunc) poll, NULL);

	/* Ask the window manager/compositor to present the window. */
	gtk_window_present (window);
}

int
main (int   argc,
      char *argv[])
{
	g_autoptr(GtkApplication) app = NULL;
	int ret;

	/* Set up gettext translations */
	bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);

	/*
	 * Create a new GtkApplication. The application manages our main loop,
	 * application windows, integration with the window manager/compositor, and
	 * desktop features such as file opening and single-instance applications.
	 */
	app = gtk_application_new ("me.appadeia.WeatherWidget", G_APPLICATION_FLAGS_NONE);

	/*
	 * We connect to the activate signal to create a window when the application
	 * has been lauched. Additionally, this signal notifies us when the user
	 * tries to launch a "second instance" of the application. When they try
	 * to do that, we'll just present any existing window.
	 *
	 * Because we can't pass a pointer to any function type, we have to cast
	 * our "on_activate" function to a GCallback.
	 */
	g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL);

	/*
	 * Run the application. This function will block until the applicaiton
	 * exits. Upon return, we have our exit code to return to the shell. (This
	 * is the code you see when you do `echo $?` after running a command in a
	 * terminal.
	 *
	 * Since GtkApplication inherits from GApplication, we use the parent class
	 * method "run". But we need to cast, which is what the "G_APPLICATION()"
	 * macro does.
	 */
	ret = g_application_run (G_APPLICATION (app), argc, argv);

	return ret;
}
