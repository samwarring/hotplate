#include <hotplate/hotplate.h>

namespace hotplate
{
	substance::substance(int current_temperature, int melting_temperature, int boiling_temperature) noexcept
		: m_temperature(current_temperature)
		, m_melting_temperature(melting_temperature)
		, m_boiling_temperature(boiling_temperature)
	{
	}

	auto substance::get_temperature() const noexcept -> int
	{
		return m_temperature;
	}

	auto substance::set_temperature(int temperature) noexcept -> void
	{
		m_temperature = temperature;
	}

	auto substance::get_state() const noexcept -> substance_state
	{
		if (m_temperature < m_melting_temperature)
			return substance_state::solid;
		else if (m_temperature < m_boiling_temperature)
			return substance_state::liquid;
		else
			return substance_state::gas;
	}

	hotplate::hotplate(int current_temperature) noexcept
		: m_temperature(current_temperature)
		, m_substance(nullptr)
	{
	}

	auto hotplate::heat_substance(substance& subst) noexcept -> bool
	{
		if (m_substance)
			return false;
		m_substance = &subst;
		m_substance->set_temperature(m_temperature);
		return true;
	}

	auto hotplate::remove_substance() noexcept -> void
	{
		m_substance = nullptr;
	}

	auto hotplate::set_temperature(int temperature) noexcept -> void
	{
		m_temperature = temperature;
		if (m_substance)
			m_substance->set_temperature(temperature);
	}

}
