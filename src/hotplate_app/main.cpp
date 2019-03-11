#include <hotplate/hotplate.h>
#include <iostream>

constexpr int HOTPLATE_START_TEMP = 288;
constexpr int WATER_START_TEMP = 288;
constexpr int WATER_MELT_TEMP = 273;
constexpr int WATER_BOIL_TEMP = 373;

auto operator<<(std::ostream& out, hotplate::substance_state state) -> std::ostream&
{
	switch (state)
	{
	case hotplate::substance_state::solid:
		out << "solid";
		break;
	case hotplate::substance_state::liquid:
		out << "liquid";
		break;
	case hotplate::substance_state::gas:
		out << "gas";
		break;
	default:
		out << "unknown";
		break;
	}
	return out;
}

auto main() -> int
{
	std::cout << "Hello, hotplate!\n";
	hotplate::hotplate hp{ HOTPLATE_START_TEMP };
	hotplate::substance water{ WATER_START_TEMP, WATER_MELT_TEMP, WATER_BOIL_TEMP };
	hp.heat_substance(water);
	for (int temp = 0; temp <= 400; temp += 50) {
		hp.set_temperature(temp);
		std::cout
			<< "Hotplate temperature " << temp << ". "
			<< "Water is " << water.get_state() << ".\n";
	}
}