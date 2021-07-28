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
	RUN_TEST_CASE(Transformations, RotationAboutXAxisMovesPoint);
	RUN_TEST_CASE(Transformations, InverseXRotationRotatesInOppositeDirection);
	RUN_TEST_CASE(Transformations, RotationAboutYAxisMovesPoint);
	RUN_TEST_CASE(Transformations, RotationAboutZAxisMovesPoint);
}

TEST_GROUP_RUNNER(Shears)
{
	RUN_TEST_CASE(Shears, ShearXInProportionToY);
	RUN_TEST_CASE(Shears, ShearXInProportionToZ);
	RUN_TEST_CASE(Shears, ShearYInProportionToX);
	RUN_TEST_CASE(Shears, ShearYInProportionToZ);
	RUN_TEST_CASE(Shears, ShearZInProportionToX);
	RUN_TEST_CASE(Shears, ShearZInProportionToY);
}

TEST_GROUP_RUNNER(TransformationSequence)
{
	RUN_TEST_CASE(TransformationSequence, IndividualTransformationsAreAppliedSequentially);
	RUN_TEST_CASE(TransformationSequence, ChainedTransformationsAreAppliedInReverseOrder);
}
