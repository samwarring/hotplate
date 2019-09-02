#ifndef _HOTPLATE_H_
#define _HOTPLATE_H_

/**
 * \brief Root namespace for all hotplate APIs
 * 
 * All classes, enums, and globals are defined in this namespace. By grouping
 * all the APIs in this namespace, hotplate APIs cannot clash with others
 * that happen to share the same name.
 */
namespace hotplate
{
	/**
	 * \brief The state of matter for a substance
	 * 
	 * \note These enum values cannot be converted to integral types.
	 */
	enum class substance_state
	{
		solid,
		liquid,
		gas
	};

	
	/** 
	 * \brief Substances are heated by \ref hotplate::hotplate objects.
	 * 
	 * Each substance maintains its internal temperature. A hotplate
	 * manipulates the substance from its \ref set_temperature method.
	 * 
	 * \note The temperature values maintained by this class are
	 *       measured in Kelvin.
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

		/**
		 * \brief Constructs a new substance with specific properties
		 * 
		 * \param current_temperature  Initial temperature of the substance
		 * \param melting_temperature  Temperature threshold between solid and liquid
		 * \param boiling_temperature  Temperature threshold between liquid and gas
		 */
		substance(int current_temperature, int melting_temperature, int boiling_temperature) noexcept;

		/**
		 * \brief Get the current temperature of the substance
		 * 
		 * \return Current temperature measured in Kelvin
		 */
		auto get_temperature() const noexcept -> int;

		/**
		 * \brief Set the current temperature of the substance
		 * 
		 * \param temperature  New temperature measured in Kelvin.
		 */
		auto set_temperature(int temperature) noexcept -> void;

		/**
		 * \brief get the substance's current state of matter
		 * 
		 * \return State of matter from the \ref substance_state enum.
		 */
		auto get_state() const noexcept -> substance_state;
	};
	

	/**
	 * \brief Hotplates are surfaces on which \ref substance objects are heated
	 * 
	 * Each hotplate object can only heat one \ref substance object at a time.
	 * Clients select a substance to heat with the \ref heat_substance method.
	 * Then, as the client changes the hotplate temperature with \ref set_temperature,
	 * the substance's temperature is updated accordingly.
	 * 
	 * \note Obviously, hotplates don't work like this in real life. In real life,
	 *       if you changed the temperature of the hotplate, the substance's temperature
	 *       would not respond immediately. Perhaps in a later version, this can be
	 *       improved.
	 */
	class hotplate
	{
	private:
		// Temperature of the hotplate (in Kelvin).
		int m_temperature;

		// Substance currently occupying the hotplate
		substance *m_substance;

	public:
		/**
		 * \brief Consructs a new hotplate with an initial temperature
		 * 
		 * \param current_temperature  Initial temperature (in Kelvin)
		 */
		hotplate(int current_temperature) noexcept;

		/**
		 * \brief Changes the temperature of the hotplate
		 * 
		 * \param temperature  New temperature (in Kelvin)
		 */
		auto set_temperature(int temperature) noexcept -> void;

		/** 
		 * \brief Puts a new substance on the hotplate. 
		 * 
		 * \param subst The substance to heat on the hotplate.
		 * 
		 * \return False if the hotplate already has a substance on it.
		 *         Otherwise, return true.
		 * 
		 * \see remove_substance
		 */
		auto heat_substance(substance& subst) noexcept -> bool;

		/**
		 * \brief Take the current substance off of the hotplate.
		 * 
		 * Removes the substance from the hotplate so that the
		 * hotplate no longer influences its temperature. Future
		 * calls to \ref set_temperature will no longer affect
		 * the substance. To heat a new substance, use the \ref
		 * heat_substance method.
		 */
		auto remove_substance() noexcept -> void;
	};
}

#endif