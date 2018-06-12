#!/bin/bash

################################################################################################################################################################

# @project        Library/Core
# @file           tools/ci/coverage.sh
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        TBD

################################################################################################################################################################

script_directory="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

project_directory="${script_directory}/../.."
docker_directory="${script_directory}/../docker"

source "${docker_directory}/.env"

docker run \
--rm \
--volume="${project_directory}:/app:rw" \
--volume="/app/build" \
--workdir="/app/build" \
${image_name} \
/bin/bash -c "cmake -DBUILD_CODE_COVERAGE=ON .. && make coverage && bash <(curl -s https://codecov.io/bash) -X gcov -y ../../.codecov.yml || echo 'Codecov did not collect coverage reports'"

################################################################################################################################################################