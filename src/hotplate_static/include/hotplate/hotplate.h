#ifndef _HOTPLATE_H_
#define _HOTPLATE_H_

/**
 * \brief This is the brief description
 * 
 * This is the root namespace for all APIs defined by the Hotplate library.
 * Having a root namespace like this for an external library is a good idea
 * because it prevents our API names from clashing with other external 
 * libraries.
 * 
 *   \warning  This is a warning
 *   \note This is a note
 */
namespace hotplate
{
	/**
	 * The state of matter for a substance
	 * \warning this is a warning in an enum description
	 */
	enum class substance_state
	{
		solid,   ///< The substance is a solid.
		liquid,  ///< The substance is a liquid.
		gas      ///< The substance is a gas.
	};

	
	/** Substances can be "put on" hotplates and react differently.
	 * \warning this is a warning on a class description
	 */
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

		/// Gets the current temperature.
		/// \warning this is a warning on a method description
		auto get_temperature() const noexcept -> int;

		// Sets the current temperature.
		auto set_temperature(int temperature) noexcept -> void;

		// Gets the current state of the substance
		auto get_state() const noexcept -> substance_state;
	};
	

	/** Hotplates heat up substances.
	 */
	class hotplate
	{
	private:
		// Temperature of the hotplate (in Kelvin).
		int m_temperature;

		// Substance currently occupying the hotplate
		substance *m_substance;

	public:
		hotplate(int current_temperature) noexcept;

		//! Sets the current temperature (in Kelvin)
		// \param temperature temperature in Kelvin
		auto set_temperature(int temperature) noexcept -> void;

		/** Puts a new substance on the hotplate. Returns false if
		 * the hotplate is already in use.
		 * 
		 * \param subst The substance to heat on the hotplate.
		 */
		auto heat_substance(substance& subst) noexcept -> bool;

		//! Removes the substance from the hotplate.
		auto remove_substance() noexcept -> void;
	};
}

#endif