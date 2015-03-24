//Container for http header fields
#ifndef HTTP_HEADERS_H_
#define HTTP_HEADERS_H_

#include <unordered_map>
#include <string>
#include <iosfwd>

namespace http {
	
	class Headers {
	public:
		typedef std::unordered_map<std::string, std::string> map_type;

	public:
		Headers();
		Headers(std::istream &in);
		Headers(const Headers &) = default;
		Headers(Headers &&);
		Headers(const map_type &map);

		Headers &operator=(const Headers &) = default;
		Headers &operator=(Headers &&);

		void addValue(const std::string &field, const std::string &value);
		void addValue(const std::string &field, int value);

		bool hasValue(const std::string &field) const;

		bool removeValue(const std::string &field);

		std::string getString(const std::string &field, const std::string &defaultValue = "") const;
		int getInt(const std::string &field, int defaultValue = -1) const;

		std::string toString() const;
		void parse(std::istream &in);

	private:
		map_type values_;
	};

}

#endif /*HTTP_HEADERS_H_*/