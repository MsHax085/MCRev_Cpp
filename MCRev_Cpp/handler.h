class Handler {
	public:
		Handler(void);
		bool handler_start(void);
		void handler_stop(void);
	private:
		static bool EXECUTE;
		static bool STOPPED;
		void* thread;
		static unsigned long __stdcall handler_execute(void* data);
		static void setExecute(bool);
		static void setStopped(bool);
		static bool getExecute(void);
		static bool getStopped(void);
};