#include "catch_amalgamated.hpp"
#include "../great_indiction.h"
#include <array>
#include <string>

namespace gi = great_indiction;
using gi::GREAT_INDICTION_LENGTH;
using MD = gi::MonthDay ;


namespace Catch {
    template<>
    struct StringMaker<MD> {
        static std::string convert( MD const& val ) {
            return "{" + std::to_string(val.first) + ',' + std::to_string(val.second) + '}' ;
        }
    };
}


std::ostream& operator << ( std::ostream& os, const gi::DayProperty p ) {
  os << "DayProperty::" ;
  switch (p) {
    using enum gi::DayProperty ;
    case EASTER:
      os << "EASTER";
      break;
    case BRIGHT_MON:
      os << "BRIGHT_MON";
      break;
    case BRIGHT_TUE:
      os << "BRIGHT_TUE";
      break;
    case BRIGHT_WED:
      os << "BRIGHT_WED";
      break;
    case BRIGHT_THU:
      os << "BRIGHT_THU";
      break;
    case BRIGHT_FRI:
      os << "BRIGHT_FRI";
      break;
    case BRIGHT_SAT:
      os << "BRIGHT_SAT";
      break;
    case SUN2_AFTER_EASTER:
      os << "SUN2_AFTER_EASTER";
      break;
    case WEEK2_AFTER_EASTER_MON:
      os << "WEEK2_AFTER_EASTER_MON";
      break;
    case WEEK2_AFTER_EASTER_TUE:
      os << "WEEK2_AFTER_EASTER_TUE";
      break;
    case WEEK2_AFTER_EASTER_WED:
      os << "WEEK2_AFTER_EASTER_WED";
      break;
    case WEEK2_AFTER_EASTER_THU:
      os << "WEEK2_AFTER_EASTER_THU";
      break;
    case WEEK2_AFTER_EASTER_FRI:
      os << "WEEK2_AFTER_EASTER_FRI";
      break;
    case WEEK2_AFTER_EASTER_SAT:
      os << "WEEK2_AFTER_EASTER_SAT";
      break;
    case SUN3_AFTER_EASTER:
      os << "SUN3_AFTER_EASTER";
      break;
    case WEEK3_AFTER_EASTER_MON:
      os << "WEEK3_AFTER_EASTER_MON";
      break;
    case WEEK3_AFTER_EASTER_TUE:
      os << "WEEK3_AFTER_EASTER_TUE";
      break;
    case WEEK3_AFTER_EASTER_WED:
      os << "WEEK3_AFTER_EASTER_WED";
      break;
    case WEEK3_AFTER_EASTER_THU:
      os << "WEEK3_AFTER_EASTER_THU";
      break;
    case WEEK3_AFTER_EASTER_FRI:
      os << "WEEK3_AFTER_EASTER_FRI";
      break;
    case WEEK3_AFTER_EASTER_SAT:
      os << "WEEK3_AFTER_EASTER_SAT";
      break;
    case SUN4_AFTER_EASTER:
      os << "SUN4_AFTER_EASTER";
      break;
    case WEEK4_AFTER_EASTER_MON:
      os << "WEEK4_AFTER_EASTER_MON";
      break;
    case WEEK4_AFTER_EASTER_TUE:
      os << "WEEK4_AFTER_EASTER_TUE";
      break;
    case WEEK4_AFTER_EASTER_WED:
      os << "WEEK4_AFTER_EASTER_WED";
      break;
    case WEEK4_AFTER_EASTER_THU:
      os << "WEEK4_AFTER_EASTER_THU";
      break;
    case WEEK4_AFTER_EASTER_FRI:
      os << "WEEK4_AFTER_EASTER_FRI";
      break;
    case WEEK4_AFTER_EASTER_SAT:
      os << "WEEK4_AFTER_EASTER_SAT";
      break;
    case SUN5_AFTER_EASTER:
      os << "SUN5_AFTER_EASTER";
      break;
    case WEEK5_AFTER_EASTER_MON:
      os << "WEEK5_AFTER_EASTER_MON";
      break;
    case WEEK5_AFTER_EASTER_TUE:
      os << "WEEK5_AFTER_EASTER_TUE";
      break;
    case WEEK5_AFTER_EASTER_WED:
      os << "WEEK5_AFTER_EASTER_WED";
      break;
    case WEEK5_AFTER_EASTER_THU:
      os << "WEEK5_AFTER_EASTER_THU";
      break;
    case WEEK5_AFTER_EASTER_FRI:
      os << "WEEK5_AFTER_EASTER_FRI";
      break;
    case WEEK5_AFTER_EASTER_SAT:
      os << "WEEK5_AFTER_EASTER_SAT";
      break;
    case SUN6_AFTER_EASTER:
      os << "SUN6_AFTER_EASTER";
      break;
    case WEEK6_AFTER_EASTER_MON:
      os << "WEEK6_AFTER_EASTER_MON";
      break;
    case WEEK6_AFTER_EASTER_TUE:
      os << "WEEK6_AFTER_EASTER_TUE";
      break;
    case WEEK6_AFTER_EASTER_WED:
      os << "WEEK6_AFTER_EASTER_WED";
      break;
    case WEEK6_AFTER_EASTER_THU:
      os << "WEEK6_AFTER_EASTER_THU";
      break;
    case WEEK6_AFTER_EASTER_FRI:
      os << "WEEK6_AFTER_EASTER_FRI";
      break;
    case WEEK6_AFTER_EASTER_SAT:
      os << "WEEK6_AFTER_EASTER_SAT";
      break;
    case SUN7_AFTER_EASTER:
      os << "SUN7_AFTER_EASTER";
      break;
    case WEEK7_AFTER_EASTER_MON:
      os << "WEEK7_AFTER_EASTER_MON";
      break;
    case WEEK7_AFTER_EASTER_TUE:
      os << "WEEK7_AFTER_EASTER_TUE";
      break;
    case WEEK7_AFTER_EASTER_WED:
      os << "WEEK7_AFTER_EASTER_WED";
      break;
    case WEEK7_AFTER_EASTER_THU:
      os << "WEEK7_AFTER_EASTER_THU";
      break;
    case WEEK7_AFTER_EASTER_FRI:
      os << "WEEK7_AFTER_EASTER_FRI";
      break;
    case WEEK7_AFTER_EASTER_SAT:
      os << "WEEK7_AFTER_EASTER_SAT";
      break;
    case PENTECOST_SUN:
      os << "PENTECOST_SUN";
      break;
    case PENTECOST_MON:
      os << "PENTECOST_MON";
      break;
    case PENTECOST_TUE:
      os << "PENTECOST_TUE";
      break;
    case PENTECOST_WED:
      os << "PENTECOST_WED";
      break;
    case PENTECOST_THU:
      os << "PENTECOST_THU";
      break;
    case PENTECOST_FRI:
      os << "PENTECOST_FRI";
      break;
    case PENTECOST_SAT:
      os << "PENTECOST_SAT";
      break;
    case SUN1_AFTER_PENTECOST:
      os << "SUN1_AFTER_PENTECOST";
      break;
    case SUN2_AFTER_PENTECOST:
      os << "SUN2_AFTER_PENTECOST";
      break;
    case SUN3_AFTER_PENTECOST:
      os << "SUN3_AFTER_PENTECOST";
      break;
    case SUN4_AFTER_PENTECOST:
      os << "SUN4_AFTER_PENTECOST";
      break;
    case PUBLICAN_PHARISEE_SUN:
      os << "PUBLICAN_PHARISEE_SUN";
      break;
    case PRODIGAL_SON_SUN:
      os << "PRODIGAL_SON_SUN";
      break;
    case MEMORIAL_SAT:
      os << "MEMORIAL_SAT";
      break;
    case DREAD_JUDGEMENT_SUN:
      os << "DREAD_JUDGEMENT_SUN";
      break;
    case CHEESE_MON:
      os << "CHEESE_MON";
      break;
    case CHEESE_TUE:
      os << "CHEESE_TUE";
      break;
    case CHEESE_WED:
      os << "CHEESE_WED";
      break;
    case CHEESE_THU:
      os << "CHEESE_THU";
      break;
    case CHEESE_FRI:
      os << "CHEESE_FRI";
      break;
    case CHEESE_SAT:
      os << "CHEESE_SAT";
      break;
    case CHEESE_SUN:
      os << "CHEESE_SUN";
      break;
    case LENT_WEEK1_MON:
      os << "LENT_WEEK1_MON";
      break;
    case LENT_WEEK1_TUE:
      os << "LENT_WEEK1_TUE";
      break;
    case LENT_WEEK1_WED:
      os << "LENT_WEEK1_WED";
      break;
    case LENT_WEEK1_THU:
      os << "LENT_WEEK1_THU";
      break;
    case LENT_WEEK1_FRI:
      os << "LENT_WEEK1_FRI";
      break;
    case LENT_WEEK1_SAT:
      os << "LENT_WEEK1_SAT";
      break;
    case LENT_SUN1:
      os << "LENT_SUN1";
      break;
    case LENT_WEEK2_MON:
      os << "LENT_WEEK2_MON";
      break;
    case LENT_WEEK2_TUE:
      os << "LENT_WEEK2_TUE";
      break;
    case LENT_WEEK2_WED:
      os << "LENT_WEEK2_WED";
      break;
    case LENT_WEEK2_THU:
      os << "LENT_WEEK2_THU";
      break;
    case LENT_WEEK2_FRI:
      os << "LENT_WEEK2_FRI";
      break;
    case LENT_WEEK2_SAT:
      os << "LENT_WEEK2_SAT";
      break;
    case LENT_SUN2:
      os << "LENT_SUN2";
      break;
    case LENT_WEEK3_MON:
      os << "LENT_WEEK3_MON";
      break;
    case LENT_WEEK3_TUE:
      os << "LENT_WEEK3_TUE";
      break;
    case LENT_WEEK3_WED:
      os << "LENT_WEEK3_WED";
      break;
    case LENT_WEEK3_THU:
      os << "LENT_WEEK3_THU";
      break;
    case LENT_WEEK3_FRI:
      os << "LENT_WEEK3_FRI";
      break;
    case LENT_WEEK3_SAT:
      os << "LENT_WEEK3_SAT";
      break;
    case LENT_SUN3:
      os << "LENT_SUN3";
      break;
    case LENT_WEEK4_MON:
      os << "LENT_WEEK4_MON";
      break;
    case LENT_WEEK4_TUE:
      os << "LENT_WEEK4_TUE";
      break;
    case LENT_WEEK4_WED:
      os << "LENT_WEEK4_WED";
      break;
    case LENT_WEEK4_THU:
      os << "LENT_WEEK4_THU";
      break;
    case LENT_WEEK4_FRI:
      os << "LENT_WEEK4_FRI";
      break;
    case LENT_WEEK4_SAT:
      os << "LENT_WEEK4_SAT";
      break;
    case LENT_SUN4:
      os << "LENT_SUN4";
      break;
    case LENT_WEEK5_MON:
      os << "LENT_WEEK5_MON";
      break;
    case LENT_WEEK5_TUE:
      os << "LENT_WEEK5_TUE";
      break;
    case LENT_WEEK5_WED:
      os << "LENT_WEEK5_WED";
      break;
    case LENT_WEEK5_THU:
      os << "LENT_WEEK5_THU";
      break;
    case LENT_WEEK5_FRI:
      os << "LENT_WEEK5_FRI";
      break;
    case LENT_WEEK5_SAT:
      os << "LENT_WEEK5_SAT";
      break;
    case LENT_SUN5:
      os << "LENT_SUN5";
      break;
    case LENT_WEEK6_MON:
      os << "LENT_WEEK6_MON";
      break;
    case LENT_WEEK6_TUE:
      os << "LENT_WEEK6_TUE";
      break;
    case LENT_WEEK6_WED:
      os << "LENT_WEEK6_WED";
      break;
    case LENT_WEEK6_THU:
      os << "LENT_WEEK6_THU";
      break;
    case LENT_WEEK6_FRI:
      os << "LENT_WEEK6_FRI";
      break;
    case LENT_WEEK6_SAT:
      os << "LENT_WEEK6_SAT";
      break;
    case LENT_SUN7:
      os << "LENT_SUN7";
      break;
    case LENT_WEEK7_MON:
      os << "LENT_WEEK7_MON";
      break;
    case LENT_WEEK7_TUE:
      os << "LENT_WEEK7_TUE";
      break;
    case LENT_WEEK7_WED:
      os << "LENT_WEEK7_WED";
      break;
    case LENT_WEEK7_THU:
      os << "LENT_WEEK7_THU";
      break;
    case LENT_WEEK7_FRI:
      os << "LENT_WEEK7_FRI";
      break;
    case LENT_WEEK7_SAT:
      os << "LENT_WEEK7_SAT";
      break;
    case SAT_BEFORE_EXALTATION:
      os << "SAT_BEFORE_EXALTATION";
      break;
    case SUN_BEFORE_EXALTATION:
      os << "SUN_BEFORE_EXALTATION";
      break;
    case SAT_AFTER_EXALTATION:
      os << "SAT_AFTER_EXALTATION";
      break;
    case SUN_AFTER_EXALTATION:
      os << "SUN_AFTER_EXALTATION";
      break;
    case FATHERS_ECU_COUNCIL_7:
      os << "FATHERS_ECU_COUNCIL_7";
      break;
    case DIMITRI_SAT:
      os << "DIMITRI_SAT";
      break;
    case HOLY_FOREFATHERS_SUN:
      os << "HOLY_FOREFATHERS_SUN";
      break;
    case SAT_BEFORE_CHRISTMAS:
      os << "SAT_BEFORE_CHRISTMAS";
      break;
    case SUN_BEFORE_CHRISTMAS:
      os << "SUN_BEFORE_CHRISTMAS";
      break;
    case SAT_AFTER_CHRISTMAS:
      os << "SAT_AFTER_CHRISTMAS";
      break;
    case SAT_AFTER_CHRISTMAS_READINGS:
      os << "SAT_AFTER_CHRISTMAS_READINGS";
      break;
    case SUN_AFTER_CHRISTMAS:
      os << "SUN_AFTER_CHRISTMAS";
      break;
    case SUN_AFTER_CHRISTMAS_READINGS:
      os << "SUN_AFTER_CHRISTMAS_READINGS";
      break;
    case SAINTS_JOSEPH_DAVID_JAMES:
      os << "SAINTS_JOSEPH_DAVID_JAMES";
      break;
    case SAT_BEFORE_BAPTISM:
      os << "SAT_BEFORE_BAPTISM";
      break;
    case SAT_BEFORE_BAPTISM_READINGS:
      os << "SAT_BEFORE_BAPTISM_READINGS";
      break;
    case SUN_BEFORE_BAPTISM:
      os << "SUN_BEFORE_BAPTISM";
      break;
    case SUN_BEFORE_BAPTISM_READINGS:
      os << "SUN_BEFORE_BAPTISM_READINGS";
      break;
    case SAT_AFTER_BAPTISM:
      os << "SAT_AFTER_BAPTISM";
      break;
    case SUN_AFTER_BAPTISM:
      os << "SUN_AFTER_BAPTISM";
      break;
    case NEW_MARTYRS_OF_RUSSIA:
      os << "NEW_MARTYRS_OF_RUSSIA";
      break;
    case CONVENTION_OF_3_HIERARCHS:
      os << "CONVENTION_OF_3_HIERARCHS";
      break;
    case FOREFEAST_GOD_MEETING:
      os << "FOREFEAST_GOD_MEETING";
      break;
    case GOD_MEETING:
      os << "GOD_MEETING";
      break;
    case AFTERFEAST_GOD_MEETING1:
      os << "AFTERFEAST_GOD_MEETING1";
      break;
    case AFTERFEAST_GOD_MEETING2:
      os << "AFTERFEAST_GOD_MEETING2";
      break;
    case AFTERFEAST_GOD_MEETING3:
      os << "AFTERFEAST_GOD_MEETING3";
      break;
    case AFTERFEAST_GOD_MEETING4:
      os << "AFTERFEAST_GOD_MEETING4";
      break;
    case AFTERFEAST_GOD_MEETING5:
      os << "AFTERFEAST_GOD_MEETING5";
      break;
    case AFTERFEAST_GOD_MEETING6:
      os << "AFTERFEAST_GOD_MEETING6";
      break;
    case ENDOF_GOD_MEETING:
      os << "ENDOF_GOD_MEETING";
      break;
    case JOHN_BAPTIST_HEAD_DISCOVERY_1_2:
      os << "JOHN_BAPTIST_HEAD_DISCOVERY_1_2";
      break;
    case JOHN_BAPTIST_HEAD_DISCOVERY_3:
      os << "JOHN_BAPTIST_HEAD_DISCOVERY_3";
      break;
    case HOLY_FORTY_MARTYRS_OF_SEBASTE:
      os << "HOLY_FORTY_MARTYRS_OF_SEBASTE";
      break;
    case FOREFEAST_GOD_MOTHER_ANNUNCIATION:
      os << "FOREFEAST_GOD_MOTHER_ANNUNCIATION";
      break;
    case ENDOF_GOD_MOTHER_ANNUNCIATION:
      os << "ENDOF_GOD_MOTHER_ANNUNCIATION";
      break;
    case HOLY_GREAT_MARTYR_GEORGE:
      os << "HOLY_GREAT_MARTYR_GEORGE";
      break;
    case FATHERS_ECU_COUNCIL_1_6:
      os << "FATHERS_ECU_COUNCIL_1_6";
      break;
    case MOVEABLE_FEAST:
      os << "MOVEABLE_FEAST";
      break;
    case IMMOVEABLE_FEAST:
      os << "IMMOVEABLE_FEAST";
      break;
    case GREAT_FEAST:
      os << "GREAT_FEAST";
      break;
    case GREAT_LENT:
      os << "GREAT_LENT";
      break;
    case APOSTOL_LENT:
      os << "APOSTOL_LENT";
      break;
    case CHRISTMAS_LENT:
      os << "CHRISTMAS_LENT";
      break;
    case ASSUMPTION_LENT:
      os << "ASSUMPTION_LENT";
      break;
    case SOLID_WEEK_BRIGHT:
      os << "SOLID_WEEK_BRIGHT";
      break;
    case SOLID_WEEK_CHRISTMAS:
      os << "SOLID_WEEK_CHRISTMAS";
      break;
    case SOLID_WEEK_PENTECOST:
      os << "SOLID_WEEK_PENTECOST";
      break;
    case SOLID_WEEK_CHEESE:
      os << "SOLID_WEEK_CHEESE";
      break;
    case SOLID_WEEK_PUBLICAN_PHARISEE:
      os << "SOLID_WEEK_PUBLICAN_PHARISEE";
      break;
    case DAY_PROPERTY_ENUM_SIZE_:
      os << "DAY_PROPERTY_ENUM_SIZE_";
      break;
  }
  return os;
}


TEST_CASE("проверка find_date на обработку всех DayProperty"){
  auto sz = static_cast<int>(gi::DAY_PROPERTY_ENUM_SIZE_) ;
  for (int y=1; y<=GREAT_INDICTION_LENGTH; ++y) for (int i=0; i<sz; ++i) {
    auto p = static_cast<gi::DayProperty>(i) ;
    DYNAMIC_SECTION("DayProperty = " << p){
      auto md = gi::find_date(y, p);
      REQUIRE( md.first>0 && md.second>0 ) ;
    }
  }
}


TEST_CASE("проверка расчета даты пасхи"){
  constexpr std::array arr = {
    MD(4,7),
    MD(3,23),
    MD(4,12),
    MD(4,3),
    MD(4,23),
    MD(4,8),
    MD(3,31),
    MD(4,19),
    MD(4,11),
    MD(3,27),
    MD(4,16),
    MD(4,7),
    MD(3,23),
    MD(4,12),
    MD(4,4),
    MD(4,23),
    MD(4,8),
    MD(3,31),
    MD(4,20),
    MD(4,4),
    MD(3,27),
    MD(4,16),
    MD(4,1),
    MD(4,20),
    MD(4,12),
    MD(3,28),
    MD(4,17),
    MD(4,8),
    MD(3,31),
    MD(4,13),
    MD(4,5),
    MD(3,27),
    MD(4,16),
    MD(4,1),
    MD(4,21),
    MD(4,12),
    MD(3,28),
    MD(4,17),
    MD(4,9),
    MD(3,24),
    MD(4,13),
    MD(4,5),
    MD(4,25),
    MD(4,9),
    MD(4,1),
    MD(4,21),
    MD(4,6),
    MD(3,28),
    MD(4,17),
    MD(4,2),
    MD(3,25),
    MD(4,13),
    MD(4,5),
    MD(4,18),
    MD(4,10),
    MD(4,1),
    MD(4,14),
    MD(4,6),
    MD(3,29),
    MD(4,17),
    MD(4,2),
    MD(4,22),
    MD(4,14),
    MD(3,29),
    MD(4,18),
    MD(4,10),
    MD(3,26),
    MD(4,14),
    MD(4,6),
    MD(3,22),
    MD(4,11),
    MD(4,2),
    MD(4,22),
    MD(4,7),
    MD(3,30),
    MD(4,18),
    MD(4,3),
    MD(3,26),
    MD(4,15),
    MD(4,6),
    MD(4,19),
    MD(4,11),
    MD(4,3),
    MD(4,22),
    MD(4,7),
    MD(3,30),
    MD(4,19),
    MD(4,3),
    MD(3,26),
    MD(4,15),
    MD(3,31),
    MD(4,19),
    MD(4,11),
    MD(3,27),
    MD(4,16),
    MD(4,7),
    MD(3,23),
    MD(4,12),
    MD(4,4),
    MD(4,23),
    MD(4,8),
    MD(3,31),
    MD(4,20),
    MD(4,11),
    MD(3,27),
    MD(4,16),
    MD(4,8),
    MD(3,23),
    MD(4,12),
    MD(4,4),
    MD(4,24),
    MD(4,8),
    MD(3,31),
    MD(4,20),
    MD(4,5),
    MD(3,27),
    MD(4,16),
    MD(4,1),
    MD(4,21),
    MD(4,12),
    MD(3,28),
    MD(4,17),
    MD(4,9),
    MD(3,31),
    MD(4,13),
    MD(4,5),
    MD(3,28),
    MD(4,16),
    MD(4,1),
    MD(4,21),
    MD(4,6),
    MD(3,28),
    MD(4,17),
    MD(4,9),
    MD(3,25),
    MD(4,13),
    MD(4,5),
    MD(4,25),
    MD(4,10),
    MD(4,1),
    MD(4,21),
    MD(4,6),
    MD(3,29),
    MD(4,17),
    MD(4,2),
    MD(3,25),
    MD(4,14),
    MD(4,5),
    MD(4,18),
    MD(4,10),
    MD(3,26),
    MD(4,14),
    MD(4,6),
    MD(3,29),
    MD(4,11),
    MD(4,2),
    MD(4,22),
    MD(4,14),
    MD(3,30),
    MD(4,18),
    MD(4,10),
    MD(3,26),
    MD(4,15),
    MD(4,6),
    MD(3,22),
    MD(4,11),
    MD(4,3),
    MD(4,22),
    MD(4,7),
    MD(3,30),
    MD(4,19),
    MD(4,3),
    MD(3,26),
    MD(4,15),
    MD(3,31),
    MD(4,19),
    MD(4,11),
    MD(4,3),
    MD(4,16),
    MD(4,7),
    MD(3,30),
    MD(4,19),
    MD(4,4),
    MD(3,26),
    MD(4,15),
    MD(3,31),
    MD(4,20),
    MD(4,11),
    MD(3,27),
    MD(4,16),
    MD(4,8),
    MD(3,23),
    MD(4,12),
    MD(4,4),
    MD(4,24),
    MD(4,8),
    MD(3,31),
    MD(4,20),
    MD(4,5),
    MD(3,27),
    MD(4,16),
    MD(4,8),
    MD(3,24),
    MD(4,12),
    MD(4,4),
    MD(4,24),
    MD(4,9),
    MD(3,31),
    MD(4,20),
    MD(4,5),
    MD(3,28),
    MD(4,16),
    MD(4,1),
    MD(4,21),
    MD(4,13),
    MD(3,28),
    MD(4,17),
    MD(4,9),
    MD(3,25),
    MD(4,13),
    MD(4,5),
    MD(3,28),
    MD(4,10),
    MD(4,1),
    MD(4,21),
    MD(4,6),
    MD(3,29),
    MD(4,17),
    MD(4,9),
    MD(3,25),
    MD(4,14),
    MD(4,5),
    MD(4,25),
    MD(4,10),
    MD(4,2),
    MD(4,21),
    MD(4,6),
    MD(3,29),
    MD(4,18),
    MD(4,2),
    MD(3,25),
    MD(4,14),
    MD(3,30),
    MD(4,18),
    MD(4,10),
    MD(3,26),
    MD(4,15),
    MD(4,6),
    MD(3,29),
    MD(4,11),
    MD(4,3),
    MD(4,22),
    MD(4,14),
    MD(3,30),
    MD(4,19),
    MD(4,10),
    MD(3,26),
    MD(4,15),
    MD(4,7),
    MD(3,22),
    MD(4,11),
    MD(4,3),
    MD(4,23),
    MD(4,7),
    MD(3,30),
    MD(4,19),
    MD(4,4),
    MD(3,26),
    MD(4,15),
    MD(3,31),
    MD(4,20),
    MD(4,11),
    MD(4,3),
    MD(4,16),
    MD(4,8),
    MD(3,30),
    MD(4,19),
    MD(4,4),
    MD(3,27),
    MD(4,15),
    MD(3,31),
    MD(4,20),
    MD(4,12),
    MD(3,27),
    MD(4,16),
    MD(4,8),
    MD(3,24),
    MD(4,12),
    MD(4,4),
    MD(4,24),
    MD(4,9),
    MD(3,31),
    MD(4,20),
    MD(4,5),
    MD(3,28),
    MD(4,16),
    MD(4,8),
    MD(3,24),
    MD(4,13),
    MD(4,4),
    MD(4,24),
    MD(4,9),
    MD(4,1),
    MD(4,20),
    MD(4,5),
    MD(3,28),
    MD(4,17),
    MD(4,1),
    MD(4,21),
    MD(4,13),
    MD(3,29),
    MD(4,17),
    MD(4,9),
    MD(3,25),
    MD(4,14),
    MD(4,5),
    MD(3,28),
    MD(4,10),
    MD(4,2),
    MD(4,21),
    MD(4,6),
    MD(3,29),
    MD(4,18),
    MD(4,9),
    MD(3,25),
    MD(4,14),
    MD(4,6),
    MD(4,25),
    MD(4,10),
    MD(4,2),
    MD(4,22),
    MD(4,6),
    MD(3,29),
    MD(4,18),
    MD(4,3),
    MD(3,25),
    MD(4,14),
    MD(3,30),
    MD(4,19),
    MD(4,10),
    MD(3,26),
    MD(4,15),
    MD(4,7),
    MD(3,29),
    MD(4,11),
    MD(4,3),
    MD(4,23),
    MD(4,14),
    MD(3,30),
    MD(4,19),
    MD(4,11),
    MD(3,26),
    MD(4,15),
    MD(4,7),
    MD(3,23),
    MD(4,11),
    MD(4,3),
    MD(4,23),
    MD(4,8),
    MD(3,30),
    MD(4,19),
    MD(4,4),
    MD(3,27),
    MD(4,15),
    MD(3,31),
    MD(4,20),
    MD(4,12),
    MD(4,3),
    MD(4,16),
    MD(4,8),
    MD(3,31),
    MD(4,19),
    MD(4,4),
    MD(3,27),
    MD(4,16),
    MD(3,31),
    MD(4,20),
    MD(4,12),
    MD(3,28),
    MD(4,16),
    MD(4,8),
    MD(3,24),
    MD(4,13),
    MD(4,4),
    MD(4,24),
    MD(4,9),
    MD(4,1),
    MD(4,20),
    MD(4,5),
    MD(3,28),
    MD(4,17),
    MD(4,8),
    MD(3,24),
    MD(4,13),
    MD(4,5),
    MD(4,24),
    MD(4,9),
    MD(4,1),
    MD(4,14),
    MD(4,5),
    MD(3,28),
    MD(4,17),
    MD(4,2),
    MD(4,21),
    MD(4,13),
    MD(3,29),
    MD(4,18),
    MD(4,9),
    MD(3,25),
    MD(4,14),
    MD(4,6),
    MD(3,28),
    MD(4,10),
    MD(4,2),
    MD(4,22),
    MD(4,6),
    MD(3,29),
    MD(4,18),
    MD(4,3),
    MD(3,25),
    MD(4,14),
    MD(4,6),
    MD(4,19),
    MD(4,10),
    MD(4,2),
    MD(4,22),
    MD(4,7),
    MD(3,29),
    MD(4,18),
    MD(4,3),
    MD(3,26),
    MD(4,14),
    MD(3,30),
    MD(4,19),
    MD(4,11),
    MD(3,26),
    MD(4,15),
    MD(4,7),
    MD(3,23),
    MD(4,11),
    MD(4,3),
    MD(4,23),
    MD(4,8),
    MD(3,30),
    MD(4,19),
    MD(4,11),
    MD(3,27),
    MD(4,15),
    MD(4,7),
    MD(3,23),
    MD(4,12),
    MD(4,3),
    MD(4,23),
    MD(4,8),
    MD(3,31),
    MD(4,19),
    MD(4,4),
    MD(3,27),
    MD(4,16),
    MD(3,31),
    MD(4,20),
    MD(4,12),
    MD(3,28),
    MD(4,16),
    MD(4,8),
    MD(3,31),
    MD(4,13),
    MD(4,4),
    MD(3,27),
    MD(4,16),
    MD(4,1),
    MD(4,20),
    MD(4,12),
    MD(3,28),
    MD(4,17),
    MD(4,8),
    MD(3,24),
    MD(4,13),
    MD(4,5),
    MD(4,24),
    MD(4,9),
    MD(4,1),
    MD(4,21),
    MD(4,5),
    MD(3,28),
    MD(4,17),
    MD(4,2),
    MD(3,24),
    MD(4,13),
    MD(4,5),
    MD(4,18),
    MD(4,9),
    MD(4,1),
    MD(4,14),
    MD(4,6),
    MD(3,28),
    MD(4,17),
    MD(4,2),
    MD(4,22),
    MD(4,13),
    MD(3,29),
    MD(4,18),
    MD(4,10),
    MD(3,25),
    MD(4,14),
    MD(4,6),
    MD(3,22),
    MD(4,10),
    MD(4,2),
    MD(4,22),
    MD(4,7),
    MD(3,29),
    MD(4,18),
    MD(4,3),
    MD(3,26),
    MD(4,14),
    MD(4,6),
    MD(4,19),
    MD(4,11),
    MD(4,2),
    MD(4,22),
    MD(4,7),
    MD(3,30),
    MD(4,18),
    MD(4,3),
    MD(3,26),
    MD(4,15),
    MD(3,30),
    MD(4,19),
    MD(4,11),
    MD(3,27),
    MD(4,15),
  };
  SECTION("функция easter_date"){
    for (int y=1; y<=GREAT_INDICTION_LENGTH; ++y) REQUIRE( gi::easter_date(y) == arr[y-1] ) ;
  }
  SECTION("функция is_date_of"){
    for (int y=1; y<=GREAT_INDICTION_LENGTH; ++y) REQUIRE( gi::is_date_of(y, arr[y-1], gi::PASHA) ) ;
  }
  SECTION("функция find_date"){
    for (int y=1; y<=GREAT_INDICTION_LENGTH; ++y) REQUIRE( gi::find_date(y, gi::PASHA) == arr[y-1] ) ;
  }
}


TEST_CASE("проверка расчета длины петрова поста"){
  constexpr std::array arr = {
    26,
    41,
    21,
    30,
    10,
    25,
    33,
    14,
    22,
    37,
    17,
    26,
    41,
    21,
    29,
    10,
    25,
    33,
    13,
    29,
    37,
    17,
    32,
    13,
    21,
    36,
    16,
    25,
    33,
    20,
    28,
    37,
    17,
    32,
    12,
    21,
    36,
    16,
    24,
    40,
    20,
    28,
    8,
    24,
    32,
    12,
    27,
    36,
    16,
    31,
    39,
    20,
    28,
    15,
    23,
    32,
    19,
    27,
    35,
    16,
    31,
    11,
    19,
    35,
    15,
    23,
    38,
    19,
    27,
    42,
    22,
    31,
    11,
    26,
    34,
    15,
    30,
    38,
    18,
    27,
    14,
    22,
    30,
    11,
    26,
    34,
    14,
    30,
    38,
    18,
    33,
    14,
    22,
    37,
    17,
    26,
    41,
    21,
    29,
    10,
    25,
    33,
    13,
    22,
    37,
    17,
    25,
    41,
    21,
    29,
    9,
    25,
    33,
    13,
    28,
    37,
    17,
    32,
    12,
    21,
    36,
    16,
    24,
    33,
    20,
    28,
    36,
    17,
    32,
    12,
    27,
    36,
    16,
    24,
    39,
    20,
    28,
    8,
    23,
    32,
    12,
    27,
    35,
    16,
    31,
    39,
    19,
    28,
    15,
    23,
    38,
    19,
    27,
    35,
    22,
    31,
    11,
    19,
    34,
    15,
    23,
    38,
    18,
    27,
    42,
    22,
    30,
    11,
    26,
    34,
    14,
    30,
    38,
    18,
    33,
    14,
    22,
    30,
    17,
    26,
    34,
    14,
    29,
    38,
    18,
    33,
    13,
    22,
    37,
    17,
    25,
    41,
    21,
    29,
    9,
    25,
    33,
    13,
    28,
    37,
    17,
    25,
    40,
    21,
    29,
    9,
    24,
    33,
    13,
    28,
    36,
    17,
    32,
    12,
    20,
    36,
    16,
    24,
    39,
    20,
    28,
    36,
    23,
    32,
    12,
    27,
    35,
    16,
    24,
    39,
    19,
    28,
    8,
    23,
    31,
    12,
    27,
    35,
    15,
    31,
    39,
    19,
    34,
    15,
    23,
    38,
    18,
    27,
    35,
    22,
    30,
    11,
    19,
    34,
    14,
    23,
    38,
    18,
    26,
    42,
    22,
    30,
    10,
    26,
    34,
    14,
    29,
    38,
    18,
    33,
    13,
    22,
    30,
    17,
    25,
    34,
    14,
    29,
    37,
    18,
    33,
    13,
    21,
    37,
    17,
    25,
    40,
    21,
    29,
    9,
    24,
    33,
    13,
    28,
    36,
    17,
    25,
    40,
    20,
    29,
    9,
    24,
    32,
    13,
    28,
    36,
    16,
    32,
    12,
    20,
    35,
    16,
    24,
    39,
    19,
    28,
    36,
    23,
    31,
    12,
    27,
    35,
    15,
    24,
    39,
    19,
    27,
    8,
    23,
    31,
    11,
    27,
    35,
    15,
    30,
    39,
    19,
    34,
    14,
    23,
    38,
    18,
    26,
    35,
    22,
    30,
    10,
    19,
    34,
    14,
    22,
    38,
    18,
    26,
    41,
    22,
    30,
    10,
    25,
    34,
    14,
    29,
    37,
    18,
    33,
    13,
    21,
    30,
    17,
    25,
    33,
    14,
    29,
    37,
    17,
    33,
    13,
    21,
    36,
    17,
    25,
    40,
    20,
    29,
    9,
    24,
    32,
    13,
    28,
    36,
    16,
    25,
    40,
    20,
    28,
    9,
    24,
    32,
    19,
    28,
    36,
    16,
    31,
    12,
    20,
    35,
    15,
    24,
    39,
    19,
    27,
    36,
    23,
    31,
    11,
    27,
    35,
    15,
    30,
    39,
    19,
    27,
    14,
    23,
    31,
    11,
    26,
    35,
    15,
    30,
    38,
    19,
    34,
    14,
    22,
    38,
    18,
    26,
    41,
    22,
    30,
    10,
    25,
    34,
    14,
    22,
    37,
    18,
    26,
    41,
    21,
    30,
    10,
    25,
    33,
    14,
    29,
    37,
    17,
    33,
    13,
    21,
    36,
    17,
    25,
    33,
    20,
    29,
    37,
    17,
    32,
    13,
    21,
    36,
    16,
    25,
    40,
    20,
    28,
    9,
    24,
    32,
    12,
    28,
    36,
    16,
    31,
    40,
    20,
    28,
    15,
    24,
    32,
    19,
    27,
    36,
    16,
    31,
    11,
    20,
    35,
    15,
    23,
    39,
    19,
    27,
    42,
    23,
    31,
    11,
    26,
    35,
    15,
    30,
    38,
    19,
    27,
    14,
    22,
    31,
    11,
    26,
    34,
    15,
    30,
    38,
    18,
    34,
    14,
    22,
    37,
    18,
  };
  for (int y=1; y<=GREAT_INDICTION_LENGTH; ++y) REQUIRE( gi::apostol_fast_length(y) == arr[y-1] ) ;
}
