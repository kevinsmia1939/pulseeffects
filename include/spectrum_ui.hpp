#ifndef SPECTRUM_UI_HPP
#define SPECTRUM_UI_HPP

#include <gtkmm/builder.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/grid.h>
#include <gtkmm/switch.h>
#include "application.hpp"

class SpectrumUi : public Gtk::Grid {
 public:
  SpectrumUi(BaseObjectType* cobject,
             const Glib::RefPtr<Gtk::Builder>& builder,
             const Glib::RefPtr<Gio::Settings>& refSettings,
             Application* application);

  virtual ~SpectrumUi();

 private:
  std::string log_tag = "spectrum_ui: ";

  Glib::RefPtr<Gio::Settings> settings;

  Application* app;

  Gtk::Box* spectrum_box;
  Gtk::DrawingArea* spectrum;
  Gtk::Switch *show_spectrum, *use_custom_color, *spectrum_fill;
  Gtk::ColorButton* spectrum_color_button;
  Gdk::RGBA spectrum_color;

  Glib::RefPtr<Gtk::Adjustment> spectrum_n_points, spectrum_height,
      spectrum_scale, spectrum_exponent, spectrum_sampling_freq;

  std::vector<sigc::connection> connections;

  bool mouse_inside = false;
  double mouse_intensity = 0, mouse_freq = 0;
  std::vector<float> spectrum_mag;

  void get_object(const Glib::RefPtr<Gtk::Builder>& builder,
                  const std::string& name,
                  Glib::RefPtr<Gtk::Adjustment>& object) {
    object =
        Glib::RefPtr<Gtk::Adjustment>::cast_dynamic(builder->get_object(name));
  }

  void clear_spectrum();

  bool on_show_spectrum(bool state);

  void on_spectrum_sampling_freq_set();

  bool on_use_custom_color(bool state);

  void on_new_spectrum(const std::vector<float>& magnitudes);

  bool on_spectrum_draw(const Cairo::RefPtr<Cairo::Context>& ctx);

  bool on_spectrum_enter_notify_event(GdkEventCrossing* event);

  bool on_spectrum_leave_notify_event(GdkEventCrossing* event);

  bool on_spectrum_motion_notify_event(GdkEventMotion* event);
};

#endif