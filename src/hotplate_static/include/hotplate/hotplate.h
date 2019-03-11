#ifndef _HOTPLATE_H_
#define _HOTPLATE_H_

namespace hotplate
{
	enum class substance_state
	{
		solid,
		liquid,
		gas
	};

	
	// Substances can be "put on" hotplates and react differently.
	class substance
	{
	private:
		// Temperature of the substance (in Kelvin).
		int m_temperature;

		// Temperature when the substance melts.
		int m_melting_temperature;

		// Temperature when the substance boils.
		int m_boiling_temperature;

	public:
		substance(int current_temperature, int melting_temperature, int boiling_temperature) noexcept;

		// Gets the current temperature.
		auto get_temperature() const noexcept -> int;

		// Sets the current temperature.
		auto set_temperature(int temperature) noexcept -> void;

		// Gets the current state of the substance
		auto get_state() const noexcept -> substance_state;
	};
	

	// Hotplates heat up substances.
	class hotplate
	{
	private:
		// Temperature of the hotplate (in Kelvin).
		int m_temperature;

		// Substance currently occupying the hotplate
		substance *m_substance;

	public:
		hotplate(int current_temperature) noexcept;

		// Sets the current temperature (in Kelvin)
		auto set_temperature(int temperature) noexcept -> void;

		// Puts a new substance on the hotplate. Returns false if
		// the hotplate is already in use.
		auto heat_substance(substance& subst) noexcept -> bool;

		// Removes the substance from the hotplate.
		auto remove_substance() noexcept -> void;
	};
}

#endif