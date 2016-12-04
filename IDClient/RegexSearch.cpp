#include "RegexSearch.h"
#include "XError.h"
using namespace std;
using namespace std::tr2::sys;


RegexSearch::RegexSearch(int argc, char* argv[])
{
	
}


RegexSearch::~RegexSearch()
{

}

vector<FileInfo> RegexSearch::fileInfoVec(int argc, char* argv[]) {
	path p(".");
	regex regArg(".*");
	if (argc > 1) {
		if (std::strcmp( argv[1],"-r") == 0) {
			isRecusive = true;
			if (argc > 2) {
				p = argv[2];
				if (argc > 3) {
					regArg = argv[3];
				}
			}
		}
		else {
			p = argv[1];
			if (argc > 2) {
				regArg = argv[2];
			}
		}
	}

	if (isRecusive) {
		rscan(p, regArg);
	}
	else {
		scan(p, regArg);
	}

	return results;
}

void RegexSearch::scan(path const& f, regex regArg) {
	directory_iterator d(f);
	directory_iterator e;
	for (; d != e; ++d) {

		if (!is_directory(d->status()) && regex_search(d->path().extension().string(), regArg)) {
			newFile.fileName_ = d->path().filename().string();
			++newFile.fileCount_;
			try {
				newFile.fileSize_ = file_size(d->path());
				newFile.root_ = regex_search(d->path().root_name().string(), regArg);
			}
			catch (...)
			{
				newFile.fileSize_ = 0;
			}
			if (is_directory(d->status()) && regex_search(d->path().extension().string(), regArg)) {

			}
			results.push_back(newFile);
		}// End if
	}// End for
}// End scan()

void RegexSearch::rscan(path const& f, regex regArg) {
	recursive_directory_iterator d(f);
	recursive_directory_iterator e;
	for (; d != e; ++d) {
		if (!is_directory(d->status()) && regex_search(d->path().extension().string(), regArg)) {
			newFile.fileName_ = d->path().filename().string();
			++newFile.fileCount_;
			try {
				newFile.fileSize_ = file_size(d->path());
				newFile.root_ = regex_search(d->path().filename().string(), regArg);
			}
			catch(...){
				newFile.fileSize_ = 0;
			}
			results.push_back(newFile);
		}// End if
	}// End for
}// End rscan()