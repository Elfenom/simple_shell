#!/bin/bash

# Exit immediately if any command exits with a non-zero status
set -e

# Change to the directory where the script is located
cd "$(dirname "$(readlink -f "$BASH_SOURCE")")"

# Note: see also ".mailmap" for how email addresses and names are deduplicated

{
    # Print the header for the AUTHORS file
    cat <<-'EOH'
# This file lists all individuals having contributed content to the repository.
# For how it is generated, see 'generate-authors.sh'.
EOH
    echo  # Print an empty line for separation

    # Generate a list of unique contributors from the git log
    # --format='%aN <%aE>': Format the output to show the author's name and email
    # LC_ALL=C.UTF-8: Set locale to ensure proper sorting
    # sort -uf: Sort the entries uniquely and ignore case
    git log --format='%aN <%aE>' | LC_ALL=C.UTF-8 sort -uf
} > AUTHORS  # Redirect the output to the AUTHORS file

