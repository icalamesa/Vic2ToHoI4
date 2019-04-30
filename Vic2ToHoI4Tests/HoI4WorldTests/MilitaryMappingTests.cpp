/*Copyright (c) 2019 The Paradox Game Converters Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/



#include "gtest/gtest.h"
#include "../Vic2ToHoI4/Source/HOI4World/MilitaryMappings/MilitaryMappings.h"


TEST(HoI4World_militaryMappingsTests, missingMapSectionThrowsError)
{
	std::stringstream input;
	input << "= {\n";
	input << "}";

	ASSERT_THROW(HoI4::militaryMappings theMappings(std::string(""), input), std::invalid_argument);
}


TEST(HoI4World_militaryMappingsTests, MapSectionCanBeInput)
{
	std::stringstream input;
	input << "= {\n";
	input << "\tmap = {\n";
	input << "\t}";
	input << "}";
	HoI4::militaryMappings theMappings(std::string(""), input);

	ASSERT_NO_THROW(theMappings.getUnitMap());
}


TEST(HoI4World_militaryMappingsTests, emptyDivisionTemplatesStaysEmpty)
{
	std::stringstream input(
		"= {\n"\
		"\tmap = {}\n"\
		"\tdivision_templates = {\n"\
		"\t}"\
		"}"
	);
	HoI4::militaryMappings theMappings("", input);
	ASSERT_EQ(size_t(0), theMappings.getDivisionTemplates().size());
}


TEST(HoI4World_militaryMappingsTests, TemplateAddedToDivisionTemplateMapping)
{
	std::stringstream input(
		"= {\n"\
		"\tmap = {}\n"\
		"\tdivision_templates = {\n"\
		"\t\tdivision_template = {\n"\
		"\t\t\tname = \"Light Infantry Brigade\"\n"\
		"\t\t}\n"\
		"\t}"\
		"}"
	);
	HoI4::militaryMappings theMappings("", input);
	auto templates = theMappings.getDivisionTemplates();
	ASSERT_FALSE(std::find(templates.begin(), templates.end(), "Light Infantry Brigade") == templates.end());
}


TEST(HoI4World_militaryMappingsTests, emptySubstitutesStaysEmpty)
{
	std::stringstream input(
		"= {\n"\
		"\tmap = {}\n"\
		"\tsubstitutes = {\n"\
		"\t}"\
		"}"
	);
	HoI4::militaryMappings theMappings("", input);
	ASSERT_EQ(size_t(0), theMappings.getSubstitutes().size());
}


TEST(HoI4World_militaryMappingsTests, substituteAddedToSubstitutes)
{
	std::stringstream input(
		"= {\n"\
		"\tmap = {}\n"\
		"\tsubstitutes = {\n"\
		"\t\tartillery = artillery_brigade\n"\
		"\t}"\
		"}"
	);
	HoI4::militaryMappings theMappings("", input);
	ASSERT_EQ(size_t(1), theMappings.getSubstitutes().size());
}


TEST(HoI4World_militaryMappingsTests, substituteNameInList)
{
	std::stringstream input(
		"= {\n"\
		"\tmap = {}\n"\
		"\tsubstitutes = {\n"\
		"\t\tartillery = artillery_brigade\n"\
		"\t}"\
		"}"
	);
	HoI4::militaryMappings theMappings("", input);
	ASSERT_EQ(size_t(1), theMappings.getSubstitutes().count("artillery"));
}


TEST(HoI4World_militaryMappingsTests, substituteAlternateInMapping)
{
	std::stringstream input(
		"= {\n"\
		"\tmap = {}\n"\
		"\tsubstitutes = {\n"\
		"\t\tartillery = artillery_brigade\n"\
		"\t}"\
		"}"
	);
	HoI4::militaryMappings theMappings("", input);
	ASSERT_EQ(std::string("artillery_brigade"), theMappings.getSubstitutes().at("artillery"));
}