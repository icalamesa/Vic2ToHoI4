#include "PopFactory.h"
#include "ParserHelpers.h"



Vic2::Pop::Factory::Factory(const Issues& theIssues): theIssues(theIssues)
{
	registerKeyword("size", [this](const std::string& unused, std::istream& theStream) {
		pop->size = commonItems::singleInt{theStream}.getInt();
	});
	registerKeyword("literacy", [this](const std::string& unused, std::istream& theStream) {
		pop->literacy = commonItems::singleDouble{theStream}.getDouble();
	});
	registerKeyword("mil", [this](const std::string& unused, std::istream& theStream) {
		pop->militancy = commonItems::singleDouble{theStream}.getDouble();
	});
	registerKeyword("issues", [this, &theIssues](const std::string& unused, std::istream& theStream) {
		for (const auto& assignment: commonItems::assignments{theStream}.getAssignments())
		{
			auto issueName = theIssues.getIssueName(std::stoi(assignment.first));
			pop->popIssues.insert(std::make_pair(issueName, std::stof(assignment.second)));
		}
	});

	registerKeyword("id", commonItems::ignoreItem);
	registerKeyword("con", commonItems::ignoreItem);

	registerRegex(commonItems::catchallRegex, [this](const std::string& cultureString, std::istream& theStream) {
		// only record the first matching item as culture & religion
		if (pop->culture == "no_culture")
		{
			pop->culture = cultureString;
		}
		commonItems::ignoreItem(cultureString, theStream);
	});
}


std::unique_ptr<Vic2::Pop> Vic2::Pop::Factory::getPop(const std::string& typeString, std::istream& theStream)
{
	pop = std::make_unique<Pop>();
	pop->type = typeString;

	parseStream(theStream);

	return std::move(pop);
}