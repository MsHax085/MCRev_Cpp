class Application {
	public:
		void watch_input(void);
		void handle_input(char row[]);
	private:
		bool RUN;
		void funct_start(void);
		void funct_stop(void);
		void funct_exit(void);
		void funct_help(void);
};