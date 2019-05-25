#include <hotplate/hotplate.h>
#include <hotplate/build_info.h>
#include <boost/program_options.hpp>
#include <iostream>

namespace bpo = boost::program_options;

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

auto main(int argc, char** argv) -> int
{
	// describe positional arguments
	bpo::positional_options_description pos_desc;
	pos_desc.add("name", -1);

	// describe command line options
	int start_temp = -1;
	bpo::options_description opt_desc("hotplate options");
	auto add_arg = opt_desc.add_options();
	add_arg("help,h",
	        "Write this help description");
	add_arg("version,v",
	        "print version information and exit");
	add_arg("start-temp,s",
	        bpo::value<int>(&start_temp)->default_value(0),
	        "Starting temperature");

	// parse command line
	bpo::command_line_parser parser(argc, argv);
	parser.options(opt_desc);
	parser.positional(pos_desc);
	bpo::variables_map opt_vars;
	bpo::store(parser.run(), opt_vars);
	bpo::notify(opt_vars);

	if (opt_vars.count("help")) {
		std::cout << opt_desc << '\n';
		return 0;
	}

	if (opt_vars.count("version")) {
		std::cout << "hotplate version " << hotplate::build_info::VERSION << '\n';
		return 0;
	}

	// --------
	std::cout << "Hello, hotplate!\n";
	hotplate::hotplate hp{ HOTPLATE_START_TEMP };
	hotplate::substance water{ WATER_START_TEMP, WATER_MELT_TEMP, WATER_BOIL_TEMP };
	hp.heat_substance(water);
	int final_temp = start_temp + 400;
	for (int temp = start_temp; temp <= final_temp; temp += 50) {
		hp.set_temperature(temp);
		std::cout
			<< "Hotplate temperature " << temp << ". "
			<< "Water is " << water.get_state() << ".\n";
	}
}