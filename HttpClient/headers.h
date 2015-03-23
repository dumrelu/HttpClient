//Container for http header fields
#ifndef HTTP_HEADERS_H_
#define HTTP_HEADERS_H_

#include <unordered_map>
#include <string>
#include <iosfwd>

namespace http {
	
	class Headers {
	public:
		Headers();
		Headers(std::istream &in);
		Headers(const Headers &) = default;
		Headers(Headers &&);

		Headers &operator=(const Headers &) = default;
		Headers &operator=(Headers &&);

		void addValue(const std::string &field, const std::string &value);
		void addValue(const std::string &field, int value);

		bool hasValue(const std::string &field) const;

		bool removeValue(const std::string &field);

		std::string getString(const std::string &field, const std::string &defaultValue = "") const;
		int getInt(const std::string &field, int defaultValue = -1) const;

		std::string toString() const;

	private:
		std::unordered_map<std::string, std::string> values_;
	};

}

#endif /*HTTP_HEADERS_H_*/