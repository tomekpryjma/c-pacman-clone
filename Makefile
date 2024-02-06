all:
	cd builds/unix; \
	cmake ../..; \
	make

debug:
	cd builds/debug; \
	cmake ../..; \
	make