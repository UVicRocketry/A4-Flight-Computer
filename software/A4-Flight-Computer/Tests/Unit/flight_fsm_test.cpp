#include <gtest/gtest.h>

extern "C" {
#include "flight_fsm.h"
}

TEST(FlightFsmTest, StartsInInitState) {
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_INIT);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_INIT);
}

TEST(FlightFsmTest, FollowsNominalFlightSequenceAndIgnoresInvalidEvents) {
    // current state: FLIGHT_STATE_INIT. should ignore all events except FLIGHT_EVENT_BOOT
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_ARM), FLIGHT_STATE_INIT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_LAUNCH), FLIGHT_STATE_INIT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BURNOUT), FLIGHT_STATE_INIT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_APOGEE), FLIGHT_STATE_INIT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_DROGUE), FLIGHT_STATE_INIT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_MAIN), FLIGHT_STATE_INIT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_TOUCHDOWN), FLIGHT_STATE_INIT);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_INIT);
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_INIT);

    // transition to FLIGHT_STATE_GROUND_HANDLING
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BOOT), FLIGHT_STATE_GROUND_HANDLING);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_INIT);
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_GROUND_HANDLING);

    // current state: FLIGHT_STATE_GROUND_HANDLING. should ignore all events except FLIGHT_EVENT_ARM
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BOOT), FLIGHT_STATE_GROUND_HANDLING);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_LAUNCH), FLIGHT_STATE_GROUND_HANDLING);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BURNOUT), FLIGHT_STATE_GROUND_HANDLING);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_APOGEE), FLIGHT_STATE_GROUND_HANDLING);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_DROGUE), FLIGHT_STATE_GROUND_HANDLING);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_MAIN), FLIGHT_STATE_GROUND_HANDLING);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_TOUCHDOWN), FLIGHT_STATE_GROUND_HANDLING);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_INIT);
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_GROUND_HANDLING);

    // transition to FLIGHT_STATE_PRE_LAUNCH
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_ARM), FLIGHT_STATE_PRE_LAUNCH);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_GROUND_HANDLING);
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_PRE_LAUNCH);

    // current state: FLIGHT_STATE_PRE_LAUNCH. should ignore all events except FLIGHT_EVENT_LAUNCH
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BOOT), FLIGHT_STATE_PRE_LAUNCH);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_ARM), FLIGHT_STATE_PRE_LAUNCH);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BURNOUT), FLIGHT_STATE_PRE_LAUNCH);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_APOGEE), FLIGHT_STATE_PRE_LAUNCH);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_DROGUE), FLIGHT_STATE_PRE_LAUNCH);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_MAIN), FLIGHT_STATE_PRE_LAUNCH);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_TOUCHDOWN), FLIGHT_STATE_PRE_LAUNCH);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_GROUND_HANDLING);
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_PRE_LAUNCH);


    // transition to FLIGHT_STATE_POWERED_ASCENT
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_LAUNCH), FLIGHT_STATE_POWERED_ASCENT);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_PRE_LAUNCH);
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_POWERED_ASCENT);

    // current state: FLIGHT_STATE_POWERED_ASCENT. should ignore all events except FLIGHT_EVENT_BURNOUT, FLIGHT_EVENT_DROGUE, and FLIGHT_EVENT_MAIN
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BOOT), FLIGHT_STATE_POWERED_ASCENT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_ARM), FLIGHT_STATE_POWERED_ASCENT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_LAUNCH), FLIGHT_STATE_POWERED_ASCENT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_APOGEE), FLIGHT_STATE_POWERED_ASCENT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_TOUCHDOWN), FLIGHT_STATE_POWERED_ASCENT);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_PRE_LAUNCH);
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_POWERED_ASCENT);

    // nominal sequence. transition to FLIGHT_STATE_UNPOWERED_ASCENT
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BURNOUT), FLIGHT_STATE_UNPOWERED_ASCENT);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_POWERED_ASCENT);
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_UNPOWERED_ASCENT);

    // current state: FLIGHT_STATE_UNPOWERED_ASCENT. should ignore all events except FLIGHT_EVENT_APOGEE, FLIGHT_EVENT_DROGUE, and FLIGHT_EVENT_MAIN
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BOOT), FLIGHT_STATE_UNPOWERED_ASCENT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_ARM), FLIGHT_STATE_UNPOWERED_ASCENT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_LAUNCH), FLIGHT_STATE_UNPOWERED_ASCENT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BURNOUT), FLIGHT_STATE_UNPOWERED_ASCENT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_TOUCHDOWN), FLIGHT_STATE_UNPOWERED_ASCENT);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_POWERED_ASCENT);
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_UNPOWERED_ASCENT);

    // nominal sequence. transition to FLIGHT_STATE_BALLISTIC_DESCENT
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_APOGEE), FLIGHT_STATE_BALLISTIC_DESCENT);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_UNPOWERED_ASCENT);
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_BALLISTIC_DESCENT);

    // current state: FLIGHT_STATE_BALLISTIC_DESCENT. should ignore all events except FLIGHT_EVENT_DROGUE, FLIGHT_EVENT_MAIN, and FLIGHT_EVENT_TOUCHDOWN
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BOOT), FLIGHT_STATE_BALLISTIC_DESCENT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_ARM), FLIGHT_STATE_BALLISTIC_DESCENT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_LAUNCH), FLIGHT_STATE_BALLISTIC_DESCENT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BURNOUT), FLIGHT_STATE_BALLISTIC_DESCENT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_APOGEE), FLIGHT_STATE_BALLISTIC_DESCENT);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_UNPOWERED_ASCENT);
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_BALLISTIC_DESCENT);

    // nominal sequence. transition to FLIGHT_STATE_DESCENT_DROGUE
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_DROGUE), FLIGHT_STATE_DESCENT_DROGUE);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_BALLISTIC_DESCENT);
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_DESCENT_DROGUE);

    // current state: FLIGHT_STATE_DESCENT_DROGUE. should ignore all events except FLIGHT_EVENT_MAIN and FLIGHT_EVENT_TOUCHDOWN
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BOOT), FLIGHT_STATE_DESCENT_DROGUE);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_ARM), FLIGHT_STATE_DESCENT_DROGUE);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_LAUNCH), FLIGHT_STATE_DESCENT_DROGUE);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BURNOUT), FLIGHT_STATE_DESCENT_DROGUE);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_APOGEE), FLIGHT_STATE_DESCENT_DROGUE);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_DROGUE), FLIGHT_STATE_DESCENT_DROGUE);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_BALLISTIC_DESCENT);
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_DESCENT_DROGUE);

    // nominal sequence. transition to FLIGHT_STATE_DESCENT_MAIN
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_MAIN), FLIGHT_STATE_DESCENT_MAIN);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_DESCENT_DROGUE);
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_DESCENT_MAIN);

    // current state: FLIGHT_STATE_DESCENT_MAIN. should ignore all events except FLIGHT_EVENT_TOUCHDOWN
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BOOT), FLIGHT_STATE_DESCENT_MAIN);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_ARM), FLIGHT_STATE_DESCENT_MAIN);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_LAUNCH), FLIGHT_STATE_DESCENT_MAIN);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BURNOUT), FLIGHT_STATE_DESCENT_MAIN);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_APOGEE), FLIGHT_STATE_DESCENT_MAIN);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_DROGUE), FLIGHT_STATE_DESCENT_MAIN);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_MAIN), FLIGHT_STATE_DESCENT_MAIN);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_DESCENT_DROGUE);
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_DESCENT_MAIN);

    // nominal sequence. transition to FLIGHT_STATE_RECOVERY
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_TOUCHDOWN), FLIGHT_STATE_RECOVERY);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_DESCENT_MAIN);
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_RECOVERY);

    // current state: FLIGHT_STATE_RECOVERY. should ignore all events
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BOOT), FLIGHT_STATE_RECOVERY);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_ARM), FLIGHT_STATE_RECOVERY);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_LAUNCH), FLIGHT_STATE_RECOVERY);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BURNOUT), FLIGHT_STATE_RECOVERY);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_APOGEE), FLIGHT_STATE_RECOVERY);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_DROGUE), FLIGHT_STATE_RECOVERY);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_MAIN), FLIGHT_STATE_RECOVERY);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_TOUCHDOWN), FLIGHT_STATE_RECOVERY);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_DESCENT_MAIN);
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_RECOVERY);
}

TEST(FlightFsmTest, CanTransitionToRecoveryFromBallisticDescent) {
    // transition to FLIGHT_STATE_BALLISTIC_DESCENT
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BOOT), FLIGHT_STATE_GROUND_HANDLING);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_ARM), FLIGHT_STATE_PRE_LAUNCH);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_LAUNCH), FLIGHT_STATE_POWERED_ASCENT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BURNOUT), FLIGHT_STATE_UNPOWERED_ASCENT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_APOGEE), FLIGHT_STATE_BALLISTIC_DESCENT);

    // transition to FLIGHT_STATE_RECOVERY
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_TOUCHDOWN), FLIGHT_STATE_RECOVERY);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_BALLISTIC_DESCENT);
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_RECOVERY);
}

TEST(FlightFsmTest, CanTransitionToRecoveryFromDescentDrogue) {
    // transition to FLIGHT_STATE_DESCENT_MAIN
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BOOT), FLIGHT_STATE_GROUND_HANDLING);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_ARM), FLIGHT_STATE_PRE_LAUNCH);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_LAUNCH), FLIGHT_STATE_POWERED_ASCENT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BURNOUT), FLIGHT_STATE_UNPOWERED_ASCENT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_APOGEE), FLIGHT_STATE_BALLISTIC_DESCENT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_DROGUE), FLIGHT_STATE_DESCENT_DROGUE);

    // transition to FLIGHT_STATE_RECOVERY
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_TOUCHDOWN), FLIGHT_STATE_RECOVERY);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_DESCENT_DROGUE);
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_RECOVERY);
}

TEST(FlightFsmTest, CanTransitionToDescentMainFromBallisticDescent) {
    // transition to FLIGHT_STATE_DESCENT_MAIN
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BOOT), FLIGHT_STATE_GROUND_HANDLING);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_ARM), FLIGHT_STATE_PRE_LAUNCH);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_LAUNCH), FLIGHT_STATE_POWERED_ASCENT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BURNOUT), FLIGHT_STATE_UNPOWERED_ASCENT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_APOGEE), FLIGHT_STATE_BALLISTIC_DESCENT);

    // transition to FLIGHT_STATE_DESCENT_MAIN
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_MAIN), FLIGHT_STATE_DESCENT_MAIN);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_BALLISTIC_DESCENT);
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_DESCENT_MAIN);
}

TEST(FlightFsmTest, CanTransitionToDescentMainFromPoweredAscent) {
    // transition to FLIGHT_STATE_DESCENT_MAIN
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BOOT), FLIGHT_STATE_GROUND_HANDLING);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_ARM), FLIGHT_STATE_PRE_LAUNCH);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_LAUNCH), FLIGHT_STATE_POWERED_ASCENT);

    // transition to FLIGHT_STATE_DESCENT_MAIN
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_MAIN), FLIGHT_STATE_DESCENT_MAIN);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_POWERED_ASCENT);
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_DESCENT_MAIN);
}

TEST(FlightFsmTest, CanTransitionToDescentMainFromUnpoweredAscent) {
    // transition to FLIGHT_STATE_DESCENT_MAIN
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BOOT), FLIGHT_STATE_GROUND_HANDLING);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_ARM), FLIGHT_STATE_PRE_LAUNCH);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_LAUNCH), FLIGHT_STATE_POWERED_ASCENT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BURNOUT), FLIGHT_STATE_UNPOWERED_ASCENT);

    // transition to FLIGHT_STATE_DESCENT_MAIN
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_MAIN), FLIGHT_STATE_DESCENT_MAIN);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_UNPOWERED_ASCENT);
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_DESCENT_MAIN);
}

TEST(FlightFsmTest, CanTransitionToDescentDrogueFromPoweredAscent) {
    // transition to FLIGHT_STATE_DESCENT_DROGUE
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BOOT), FLIGHT_STATE_GROUND_HANDLING);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_ARM), FLIGHT_STATE_PRE_LAUNCH);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_LAUNCH), FLIGHT_STATE_POWERED_ASCENT);

    // transition to FLIGHT_STATE_DESCENT_DROGUE
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_DROGUE), FLIGHT_STATE_DESCENT_DROGUE);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_POWERED_ASCENT);
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_DESCENT_DROGUE);
}

TEST(FlightFsmTest, CanTransitionToDescentDrogueFromUnpoweredAscent) {
    // transition to FLIGHT_STATE_DESCENT_DROGUE
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BOOT), FLIGHT_STATE_GROUND_HANDLING);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_ARM), FLIGHT_STATE_PRE_LAUNCH);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_LAUNCH), FLIGHT_STATE_POWERED_ASCENT);
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_BURNOUT), FLIGHT_STATE_UNPOWERED_ASCENT);

    // transition to FLIGHT_STATE_DESCENT_DROGUE
    EXPECT_EQ(flight_fsm_transition(FLIGHT_EVENT_DROGUE), FLIGHT_STATE_DESCENT_DROGUE);
    EXPECT_EQ(flight_fsm_get_previous_state(), FLIGHT_STATE_UNPOWERED_ASCENT);
    EXPECT_EQ(flight_fsm_get_current_state(), FLIGHT_STATE_DESCENT_DROGUE);
}