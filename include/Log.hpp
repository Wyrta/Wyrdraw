class Log
{
	private:
		static void print(int color, const char* pre, const char* log);

	public:
		static bool print_debug;

		static void debug(const char* fmt, ...);
		static void info(const char* fmt, ...);
		static void warn(const char* fmt, ...);
		static void error(const char* fmt, ...);
		static void critical(const char* fmt, ...);
};