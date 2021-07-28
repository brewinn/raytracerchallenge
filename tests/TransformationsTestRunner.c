#include "unity_fixture.h"

TEST_GROUP_RUNNER(Transformations)
{
	RUN_TEST_CASE(Transformations, TranslationMovesAPoint);
	RUN_TEST_CASE(Transformations, InverseTranslationMovesPointInOtherDirection);
	RUN_TEST_CASE(Transformations, TranslationDoesNotAffectVectors);
	RUN_TEST_CASE(Transformations, ScalingMultipliesComponents);
	RUN_TEST_CASE(Transformations, ScalingAffectsVectors);
	RUN_TEST_CASE(Transformations, InverseScalingDividesComponents);
	RUN_TEST_CASE(Transformations, NegativeScalingReflects);
}
