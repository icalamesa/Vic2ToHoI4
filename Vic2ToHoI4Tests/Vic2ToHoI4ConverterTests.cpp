#include "gtest/gtest.h"
#include "../Vic2ToHoI4/Source/Configuration.h"



void setOutputName(const std::string& V2SaveFileName);



TEST(Vic2ToHoI4Converter_setOutputNameTests, filenameEmptyWhenGivenNoInput)
{
	std::string inputName = "";
	setOutputName(inputName);
	ASSERT_EQ(std::string(""), theConfiguration.getOutputName());
}


TEST(Vic2ToHoI4Converter_setOutputNameTests, filenameCorrectWhenSimplyAName)
{
	std::string inputName = "hoi4.v2";
	setOutputName(inputName);
	ASSERT_EQ(std::string("hoi4"), theConfiguration.getOutputName());
}


TEST(Vic2ToHoI4Converter_setOutputNameTests, filenameExtractedWithWindowsPath)
{
	std::string inputName = "C:\\Users\\Cosmostarr\\Documents\\Paradox Interactive\\Victoria II\\save games\\hoi4.v2";
	setOutputName(inputName);
	ASSERT_EQ(std::string("hoi4"), theConfiguration.getOutputName());
}


TEST(Vic2ToHoI4Converter_setOutputNameTests, filenameExtractedWithLinuxPath)
{
	std::string inputName = "/Users/Cosmostarr/Documents/Paradox Interactive/Victoria II/save games/hoi4.v2";
	setOutputName(inputName);
	ASSERT_EQ(std::string("hoi4"), theConfiguration.getOutputName());
}


TEST(Vic2ToHoI4Converter_setOutputNameTests, filenameExtractedWithMixedPathEndingLinuxStyle)
{
	std::string inputName = "C:\\Users\\Cosmostarr\\Documents\\Paradox Interactive\\Victoria II\\save games/hoi4.v2";
	setOutputName(inputName);
	ASSERT_EQ(std::string("hoi4"), theConfiguration.getOutputName());
}


TEST(Vic2ToHoI4Converter_setOutputNameTests, filenameExtractedWithMixedPathEndingWindowsStyle)
{
	std::string inputName = "/Users/Cosmostarr/Documents/Paradox Interactive/Victoria II/save games\\hoi4.v2";
	setOutputName(inputName);
	ASSERT_EQ(std::string("hoi4"), theConfiguration.getOutputName());
}


TEST(Vic2ToHoI4Converter_setOutputNameTests, filenameHasDashesReplaced)
{
	std::string inputName = "hoi4-something.v2";
	setOutputName(inputName);
	ASSERT_EQ(std::string("hoi4_something"), theConfiguration.getOutputName());
}


TEST(Vic2ToHoI4Converter_setOutputNameTests, filenameHasSpacesReplaced)
{
	std::string inputName = "hoi4 something.v2";
	setOutputName(inputName);
	ASSERT_EQ(std::string("hoi4_something"), theConfiguration.getOutputName());
}


TEST(Vic2ToHoI4Converter_setOutputNameTests, filenameHasNoExtension)
{
	std::string inputName = "hoi4";
	EXPECT_THROW(setOutputName(inputName), std::invalid_argument);
}


TEST(Vic2ToHoI4Converter_setOutputNameTests, filenameHasAnInvalidExtension)
{
	std::string inputName = "hoi4.eu4";
	EXPECT_THROW(setOutputName(inputName), std::invalid_argument);
}


TEST(Vic2ToHoI4Converter_setOutputNameTests, filenameHasMultiplePeriods)
{
	std::string inputName = "hoi4.eu4.v2";
	setOutputName(inputName);
	ASSERT_EQ(std::string("hoi4.eu4"), theConfiguration.getOutputName());
}