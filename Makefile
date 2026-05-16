include common/compile_flags.mk

BUILD := build

.PHONY: help list clean all

all: help

help:
	@echo "learncpp.com study repo — usage:"
	@echo "  make 14.02     build & run a single lesson"
	@echo "  make 14        build & run all Chapter 14 lessons"
	@echo "  make 15        build & run all Chapter 15 lessons"
	@echo "  make list      list all lesson IDs"
	@echo "  make clean     remove $(BUILD)/"

list:
	@find Chapter_* -maxdepth 1 -mindepth 1 -type d 2>/dev/null \
	  | sed -E 's#.*/([0-9]+\.[0-9x]+)_.*#\1#' \
	  | sort

clean:
	@rm -rf $(BUILD)

# Catch-all dispatcher:
#   - "14.02"  → build/run one lesson
#   - "14"     → build/run every lesson in chapter 14
%:
	@id="$@"; \
	case "$$id" in \
	  *.* ) \
	    dir=""; \
	    for d in Chapter_*/$${id}_*/; do \
	      [ -d "$$d" ] && dir="$$d" && break; \
	    done; \
	    if [ -z "$$dir" ]; then \
	      echo "No lesson $$id"; exit 1; \
	    fi; \
	    mkdir -p $(BUILD)/$$id; \
	    has_header=0; \
	    for h in "$$dir"*.h "$$dir"*.hpp; do [ -f "$$h" ] && has_header=1; done; \
	    if [ $$has_header -eq 1 ] && [ -f "$$dir"main.cpp ]; then \
	      printf '── %s/main (multi-file) ──\n' "$$id"; \
	      $(CXX) $(CXXFLAGS) "$$dir"*.cpp -o "$(BUILD)/$$id/main" || exit 1; \
	      "$(BUILD)/$$id/main" || true; \
	    else \
	      found=0; \
	      for src in "$$dir"*.cpp; do \
	        [ -f "$$src" ] || continue; \
	        found=1; \
	        name=$$(basename "$$src" .cpp); \
	        printf '── %s/%s ──\n' "$$id" "$$name"; \
	        $(CXX) $(CXXFLAGS) "$$src" -o "$(BUILD)/$$id/$$name" || exit 1; \
	        "$(BUILD)/$$id/$$name" || true; \
	      done; \
	      [ $$found -eq 1 ] || echo "(no .cpp files in $$dir)"; \
	    fi ;; \
	  [0-9]* ) \
	    lessons=""; \
	    for d in Chapter_*/$${id}.*/; do \
	      [ -d "$$d" ] || continue; \
	      lid=$$(basename "$$d" | sed -E 's/_.*//'); \
	      lessons="$$lessons $$lid"; \
	    done; \
	    if [ -z "$$lessons" ]; then \
	      echo "No chapter $$id"; exit 1; \
	    fi; \
	    for l in $$lessons; do \
	      $(MAKE) --no-print-directory $$l || exit 1; \
	    done ;; \
	  * ) \
	    echo "Unknown target: $$id"; exit 1 ;; \
	esac
