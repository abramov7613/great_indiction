/*
    MIT License

    Copyright (c) 2026 Vladimir Abramov <abramov7613@yandex.ru>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once
#include <utility>

namespace great_indiction {

enum class DayProperty {
  MOVEABLE_FEAST                    ,///< Двунадесятые переходящие праздники
  IMMOVEABLE_FEAST                  ,///< Двунадесятые непереходящие праздники
  GREAT_FEAST                       ,///< Великие праздники
  EASTER                            ,///< Светлое Христово Воскресение. ПАСХА.
  BRIGHT_MON                        ,///< Понедельник Светлой седмицы.
  BRIGHT_TUE                        ,///< Вторник Светлой седмицы.
  BRIGHT_WED                        ,///< Среда Светлой седмицы.
  BRIGHT_THU                        ,///< Четверг Светлой седмицы.
  BRIGHT_FRI                        ,///< Пятница Светлой седмицы.
  BRIGHT_SAT                        ,///< Суббота Светлой седмицы.
  SUN2_AFTER_EASTER                 ,///< Неделя 2-я по Пасхе, апостола Фомы́. Антипасха.
  WEEK2_AFTER_EASTER_MON            ,///< Понедельник 2-й седмицы по Пасхе.
  WEEK2_AFTER_EASTER_TUE            ,///< Вторник 2-й седмицы по Пасхе. Ра́доница. Поминовение усопших.
  WEEK2_AFTER_EASTER_WED            ,///< Среда 2-й седмицы по Пасхе.
  WEEK2_AFTER_EASTER_THU            ,///< Четверг 2-й седмицы по Пасхе.
  WEEK2_AFTER_EASTER_FRI            ,///< Пятница 2-й седмицы по Пасхе.
  WEEK2_AFTER_EASTER_SAT            ,///< Суббота 2-й седмицы по Пасхе.
  SUN3_AFTER_EASTER                 ,///< Неделя 3-я по Пасхе, святых жен-мироносиц.
  WEEK3_AFTER_EASTER_MON            ,///< Понедельник 3-й седмицы по Пасхе.
  WEEK3_AFTER_EASTER_TUE            ,///< Вторник 3-й седмицы по Пасхе.
  WEEK3_AFTER_EASTER_WED            ,///< Среда 3-й седмицы по Пасхе.
  WEEK3_AFTER_EASTER_THU            ,///< Четверг 3-й седмицы по Пасхе.
  WEEK3_AFTER_EASTER_FRI            ,///< Пятница 3-й седмицы по Пасхе.
  WEEK3_AFTER_EASTER_SAT            ,///< Суббота 3-й седмицы по Пасхе.
  SUN4_AFTER_EASTER                 ,///< Неделя 4-я по Пасхе, о расслабленном.
  WEEK4_AFTER_EASTER_MON            ,///< Понедельник 4-й седмицы по Пасхе.
  WEEK4_AFTER_EASTER_TUE            ,///< Вторник 4-й седмицы по Пасхе.
  WEEK4_AFTER_EASTER_WED            ,///< Среда 4-й седмицы по Пасхе. Преполове́ние Пятидесятницы.
  WEEK4_AFTER_EASTER_THU            ,///< Четверг 4-й седмицы по Пасхе.
  WEEK4_AFTER_EASTER_FRI            ,///< Пятница 4-й седмицы по Пасхе.
  WEEK4_AFTER_EASTER_SAT            ,///< Суббота 4-й седмицы по Пасхе.
  SUN5_AFTER_EASTER                 ,///< Неделя 5-я по Пасхе, о самаряны́не.
  WEEK5_AFTER_EASTER_MON            ,///< Понедельник 5-й седмицы по Пасхе.
  WEEK5_AFTER_EASTER_TUE            ,///< Вторник 5-й седмицы по Пасхе.
  WEEK5_AFTER_EASTER_WED            ,///< Среда 5-й седмицы по Пасхе. Отдание праздника Преполовения Пятидесятницы.
  WEEK5_AFTER_EASTER_THU            ,///< Четверг 5-й седмицы по Пасхе.
  WEEK5_AFTER_EASTER_FRI            ,///< Пятница 5-й седмицы по Пасхе.
  WEEK5_AFTER_EASTER_SAT            ,///< Суббота 5-й седмицы по Пасхе.
  SUN6_AFTER_EASTER                 ,///< Неделя 6-я по Пасхе, о слепом.
  WEEK6_AFTER_EASTER_MON            ,///< Понедельник 6-й седмицы по Пасхе.
  WEEK6_AFTER_EASTER_TUE            ,///< Вторник 6-й седмицы по Пасхе.
  WEEK6_AFTER_EASTER_WED            ,///< Среда 6-й седмицы по Пасхе. Отдание праздника Пасхи.
  WEEK6_AFTER_EASTER_THU            ,///< Четверг 6-й седмицы по Пасхе. Вознесе́ние Госпо́дне.
  WEEK6_AFTER_EASTER_FRI            ,///< Пятница 6-й седмицы по Пасхе. Попразднство Вознесения.
  WEEK6_AFTER_EASTER_SAT            ,///< Суббота 6-й седмицы по Пасхе. Попразднство Вознесения.
  SUN7_AFTER_EASTER                 ,///< Неделя 7-я по Пасхе. Святых отцов Первого Вселенского Собора.
  WEEK7_AFTER_EASTER_MON            ,///< Понедельник 7-й седмицы по Пасхе. Попразднство Вознесения.
  WEEK7_AFTER_EASTER_TUE            ,///< Вторник 7-й седмицы по Пасхе. Попразднство Вознесения.
  WEEK7_AFTER_EASTER_WED            ,///< Среда 7-й седмицы по Пасхе. Попразднство Вознесения.
  WEEK7_AFTER_EASTER_THU            ,///< Четверг 7-й седмицы по Пасхе. Попразднство Вознесения.
  WEEK7_AFTER_EASTER_FRI            ,///< Пятница 7-й седмицы по Пасхе. Отдание праздника Вознесения Господня.
  WEEK7_AFTER_EASTER_SAT            ,///< Суббота 7-й седмицы по Пасхе. Троицкая родительская суббота.
  PENTECOST_SUN                     ,///< Неделя 8-я по Пасхе. День Святой Тро́ицы. Пятидеся́тница.
  PENTECOST_MON                     ,///< Понедельник Пятидесятницы. День Святаго Духа.
  PENTECOST_TUE                     ,///< Вторник Пятидесятницы.
  PENTECOST_WED                     ,///< Среда Пятидесятницы.
  PENTECOST_THU                     ,///< Четверг Пятидесятницы.
  PENTECOST_FRI                     ,///< Пятница Пятидесятницы.
  PENTECOST_SAT                     ,///< Суббота Пятидесятницы. Отдание праздника Пятидесятницы.
  SUN1_AFTER_PENTECOST              ,///< Неделя 1-я по Пятидесятнице, Всех святых.
  SUN2_AFTER_PENTECOST              ,///< Неделя 2-я по Пятидесятнице.
  SUN3_AFTER_PENTECOST              ,///< Неделя 3-я по Пятидесятнице.
  SUN4_AFTER_PENTECOST              ,///< Неделя 4-я по Пятидесятнице.
  SAT_BEFORE_EXALTATION             ,///< Суббота пред Воздвижением.
  SUN_BEFORE_EXALTATION             ,///< Неделя пред Воздвижением.
  SAT_AFTER_EXALTATION              ,///< Суббота по Воздвижении.
  SUN_AFTER_EXALTATION              ,///< Неделя по Воздвижении.
  FATHERS_ECU_COUNCIL_7             ,///< Память святых отцов VII Вселенского Собора.
  DIMITRI_SAT                       ,///< Димитриевская родительская суббота.
  HOLY_FOREFATHERS_SUN              ,///< Неделя святых пра́отец.
  SAT_BEFORE_CHRISTMAS              ,///< Суббота пред Рождеством Христовым.
  SUN_BEFORE_CHRISTMAS              ,///< Неделя пред Рождеством Христовым, святых отец.
  SAT_AFTER_CHRISTMAS               ,///< Суббота по Рождестве Христовом.
  SAT_AFTER_CHRISTMAS_READINGS      ,///< Чтения субботы по Рождестве Христовом.
  SUN_AFTER_CHRISTMAS               ,///< Неделя по Рождестве Христовом.
  SUN_AFTER_CHRISTMAS_READINGS      ,///< Чтения недели по Рождестве Христовом
  SAINTS_JOSEPH_DAVID_JAMES         ,///< Правв. Иосифа Обручника, Давида царя и Иакова, брата Господня.
  PUBLICAN_PHARISEE_SUN             ,///< Неделя о мытаре́ и фарисе́е.
  PRODIGAL_SON_SUN                  ,///< Неделя о блудном сыне.
  MEMORIAL_SAT                      ,///< Суббота мясопу́стная. Вселенская родительская суббота.
  DREAD_JUDGEMENT_SUN               ,///< Неделя мясопу́стная, о Страшном Суде.
  CHEESE_MON                        ,///< Понедельник сырный.
  CHEESE_TUE                        ,///< Вторник сырный.
  CHEESE_WED                        ,///< Среда сырная.
  CHEESE_THU                        ,///< Четверг сырный.
  CHEESE_FRI                        ,///< Пятница сырная.
  CHEESE_SAT                        ,///< Суббота сырная.
  CHEESE_SUN                        ,///< Неделя сыропустная. Воспоминание Адамова изгнания. Прощеное воскресенье.
  LENT_WEEK1_MON                    ,///< Понедельник 1-й седмицы. Начало Великого поста.
  LENT_WEEK1_TUE                    ,///< Вторник 1-й седмицы великого поста.
  LENT_WEEK1_WED                    ,///< Среда 1-й седмицы великого поста.
  LENT_WEEK1_THU                    ,///< Четверг 1-й седмицы великого поста.
  LENT_WEEK1_FRI                    ,///< Пятница 1-й седмицы великого поста.
  LENT_WEEK1_SAT                    ,///< Суббота 1-й седмицы великого поста.
  LENT_SUN1                         ,///< Неделя 1-я Великого поста. Торжество Православия.
  LENT_WEEK2_MON                    ,///< Понедельник 2-й седмицы великого поста.
  LENT_WEEK2_TUE                    ,///< Вторник 2-й седмицы великого поста.
  LENT_WEEK2_WED                    ,///< Среда 2-й седмицы великого поста.
  LENT_WEEK2_THU                    ,///< Четверг 2-й седмицы великого поста.
  LENT_WEEK2_FRI                    ,///< Пятница 2-й седмицы великого поста.
  LENT_WEEK2_SAT                    ,///< Суббота 2-й седмицы великого поста.
  LENT_SUN2                         ,///< Неделя 2-я Великого поста.
  LENT_WEEK3_MON                    ,///< Понедельник 3-й седмицы великого поста.
  LENT_WEEK3_TUE                    ,///< Вторник 3-й седмицы великого поста.
  LENT_WEEK3_WED                    ,///< Среда 3-й седмицы великого поста.
  LENT_WEEK3_THU                    ,///< Четверг 3-й седмицы великого поста.
  LENT_WEEK3_FRI                    ,///< Пятница 3-й седмицы великого поста.
  LENT_WEEK3_SAT                    ,///< Суббота 3-й седмицы великого поста.
  LENT_SUN3                         ,///< Неделя 3-я Великого поста, Крестопоклонная.
  LENT_WEEK4_MON                    ,///< Понедельник 4-й седмицы вел. поста, Крестопоклонной.
  LENT_WEEK4_TUE                    ,///< Вторник 4-й седмицы вел. поста, Крестопоклонной.
  LENT_WEEK4_WED                    ,///< Среда 4-й седмицы вел. поста, Крестопоклонной.
  LENT_WEEK4_THU                    ,///< Четверг 4-й седмицы вел. поста, Крестопоклонной.
  LENT_WEEK4_FRI                    ,///< Пятница 4-й седмицы вел. поста, Крестопоклонной.
  LENT_WEEK4_SAT                    ,///< Суббота 4-й седмицы вел. поста, Крестопоклонной.
  LENT_SUN4                         ,///< Неделя 4-я Великого поста. Прп. Иоанна Лествичника.
  LENT_WEEK5_MON                    ,///< Понедельник 5-й седмицы великого поста.
  LENT_WEEK5_TUE                    ,///< Вторник 5-й седмицы великого поста.
  LENT_WEEK5_WED                    ,///< Среда 5-й седмицы великого поста.
  LENT_WEEK5_THU                    ,///< Четверг 5-й седмицы великого поста.
  LENT_WEEK5_FRI                    ,///< Пятница 5-й седмицы великого поста.
  LENT_WEEK5_SAT                    ,///< Суббота 5-й седмицы великого поста. Суббота Ака́фиста. Похвала́ Пресвятой Богородицы.
  LENT_SUN5                         ,///< Неделя 5-я Великого поста. Прп. Марии Египетской
  LENT_WEEK6_MON                    ,///< Понедельник 6-й седмицы великого поста, ва́ий.
  LENT_WEEK6_TUE                    ,///< Вторник 6-й седмицы великого поста, ва́ий.
  LENT_WEEK6_WED                    ,///< Среда 6-й седмицы великого поста, ва́ий.
  LENT_WEEK6_THU                    ,///< Четверг 6-й седмицы великого поста, ва́ий.
  LENT_WEEK6_FRI                    ,///< Пятница 6-й седмицы великого поста, ва́ий.
  LENT_WEEK6_SAT                    ,///< Суббота 6-й седмицы великого поста, ва́ий. Лазарева суббота.
  LENT_SUN7                         ,///< Неделя ва́ий (цветоно́сная, Вербное воскресенье). Вход Господень в Иерусалим.
  LENT_WEEK7_MON                    ,///< Страстна́я седмица. Великий Понедельник.
  LENT_WEEK7_TUE                    ,///< Страстна́я седмица. Великий Вторник.
  LENT_WEEK7_WED                    ,///< Страстна́я седмица. Великая Среда.
  LENT_WEEK7_THU                    ,///< Страстна́я седмица. Великий Четверг. Воспоминание Тайной Ве́чери.
  LENT_WEEK7_FRI                    ,///< Страстна́я седмица. Великая Пятница.
  LENT_WEEK7_SAT                    ,///< Страстна́я седмица. Великая Суббота.
  SAT_BEFORE_BAPTISM                ,///< Суббота перед Богоявлением.
  SAT_BEFORE_BAPTISM_READINGS       ,///< Чтения субботы пред Богоявлением.
  SUN_BEFORE_BAPTISM                ,///< Неделя перед Богоявлением.
  SUN_BEFORE_BAPTISM_READINGS       ,///< Чтения недели пред Богоявлением.
  SAT_AFTER_BAPTISM                 ,///< Суббота по Богоявлении.
  SUN_AFTER_BAPTISM                 ,///< Неделя по Богоявлении.
  NEW_MARTYRS_OF_RUSSIA             ,///< Собор новомучеников и исповедников Церкви Русской.
  CONVENTION_OF_3_HIERARCHS         ,///< Собор 3-x свят. Василия Великого, Григория Богослова и Иоанна Златоустого.
  FOREFEAST_GOD_MEETING             ,///< Предпразднство Сре́тения Господня.
  GOD_MEETING                       ,///< Сре́тение Господа Бога и Спаса нашего Иисуса Христа.
  AFTERFEAST_GOD_MEETING1           ,///< День 1-й Попразднства Сретения Господня.
  AFTERFEAST_GOD_MEETING2           ,///< День 2-й Попразднства Сретения Господня.
  AFTERFEAST_GOD_MEETING3           ,///< День 3-й Попразднства Сретения Господня.
  AFTERFEAST_GOD_MEETING4           ,///< День 4-й Попразднства Сретения Господня.
  AFTERFEAST_GOD_MEETING5           ,///< День 5-й Попразднства Сретения Господня.
  AFTERFEAST_GOD_MEETING6           ,///< День 6-й Попразднства Сретения Господня.
  ENDOF_GOD_MEETING                 ,///< Отдание праздника Сретения Господня.
  JOHN_BAPTIST_HEAD_DISCOVERY_1_2   ,///< Первое и второе Обре́тение главы Иоанна Предтечи.
  JOHN_BAPTIST_HEAD_DISCOVERY_3     ,///< Третье обре́тение главы Предтечи и Крестителя Господня Иоанна.
  HOLY_FORTY_MARTYRS_OF_SEBASTE     ,///< Святых сорока́ мучеников, в Севастийском е́зере мучившихся.
  FOREFEAST_GOD_MOTHER_ANNUNCIATION ,///< Предпразднство Благовещения Пресвятой Богородицы.
  ENDOF_GOD_MOTHER_ANNUNCIATION     ,///< Отдание праздника Благовещения Пресвятой Богородицы.
  HOLY_GREAT_MARTYR_GEORGE          ,///< Вмч. Гео́ргия Победоно́сца. Мц. царицы Александры.
  FATHERS_ECU_COUNCIL_1_6           ,///< Память святых отцов шести Вселенских Соборов.
  DAY_PROPERTY_ENUM_SIZE_
}; // enum class DayProperty
using enum DayProperty ;
// таблица псевдонимов
constexpr auto MOVE_F = MOVEABLE_FEAST ;
constexpr auto IMMOVE_F = IMMOVEABLE_FEAST ;
constexpr auto GREAT_F = GREAT_FEAST ;
constexpr auto PASHA = EASTER ;
constexpr auto PASCHA = EASTER ;
constexpr auto RESURRECTION = EASTER ;
constexpr auto L_MON = BRIGHT_MON ;
constexpr auto L_TUE = BRIGHT_TUE ;
constexpr auto L_WED = BRIGHT_WED ;
constexpr auto L_THU = BRIGHT_THU ;
constexpr auto L_FRI = BRIGHT_FRI ;
constexpr auto L_SAT = BRIGHT_SAT ;
constexpr auto FOMA_SUN =   SUN2_AFTER_EASTER      ;
constexpr auto ANTIPASHA =   SUN2_AFTER_EASTER      ;
constexpr auto ANTIPASCHA =   SUN2_AFTER_EASTER      ;
constexpr auto SUN2_A_E =   SUN2_AFTER_EASTER      ;
constexpr auto RADONICA =   WEEK2_AFTER_EASTER_TUE ;
constexpr auto MID_PENTECOST = WEEK4_AFTER_EASTER_WED ;
constexpr auto W2_A_E_MON = WEEK2_AFTER_EASTER_MON ;
constexpr auto W2_A_E_TUE = WEEK2_AFTER_EASTER_TUE ;
constexpr auto W2_A_E_WED = WEEK2_AFTER_EASTER_WED ;
constexpr auto W2_A_E_THU = WEEK2_AFTER_EASTER_THU ;
constexpr auto W2_A_E_FRI = WEEK2_AFTER_EASTER_FRI ;
constexpr auto W2_A_E_SAT = WEEK2_AFTER_EASTER_SAT ;
constexpr auto SUN3_A_E =   SUN3_AFTER_EASTER      ;
constexpr auto W3_A_E_MON = WEEK3_AFTER_EASTER_MON ;
constexpr auto W3_A_E_TUE = WEEK3_AFTER_EASTER_TUE ;
constexpr auto W3_A_E_WED = WEEK3_AFTER_EASTER_WED ;
constexpr auto W3_A_E_THU = WEEK3_AFTER_EASTER_THU ;
constexpr auto W3_A_E_FRI = WEEK3_AFTER_EASTER_FRI ;
constexpr auto W3_A_E_SAT = WEEK3_AFTER_EASTER_SAT ;
constexpr auto SUN4_A_E =   SUN4_AFTER_EASTER      ;
constexpr auto W4_A_E_MON = WEEK4_AFTER_EASTER_MON ;
constexpr auto W4_A_E_TUE = WEEK4_AFTER_EASTER_TUE ;
constexpr auto W4_A_E_WED = WEEK4_AFTER_EASTER_WED ;
constexpr auto W4_A_E_THU = WEEK4_AFTER_EASTER_THU ;
constexpr auto W4_A_E_FRI = WEEK4_AFTER_EASTER_FRI ;
constexpr auto W4_A_E_SAT = WEEK4_AFTER_EASTER_SAT ;
constexpr auto SUN5_A_E =   SUN5_AFTER_EASTER      ;
constexpr auto W5_A_E_MON = WEEK5_AFTER_EASTER_MON ;
constexpr auto W5_A_E_TUE = WEEK5_AFTER_EASTER_TUE ;
constexpr auto W5_A_E_WED = WEEK5_AFTER_EASTER_WED ;
constexpr auto ENDOF_MID_PENTECOST = WEEK5_AFTER_EASTER_WED ;
constexpr auto W5_A_E_THU = WEEK5_AFTER_EASTER_THU ;
constexpr auto W5_A_E_FRI = WEEK5_AFTER_EASTER_FRI ;
constexpr auto W5_A_E_SAT = WEEK5_AFTER_EASTER_SAT ;
constexpr auto SUN6_A_E =   SUN6_AFTER_EASTER      ;
constexpr auto W6_A_E_MON = WEEK6_AFTER_EASTER_MON ;
constexpr auto W6_A_E_TUE = WEEK6_AFTER_EASTER_TUE ;
constexpr auto W6_A_E_WED = WEEK6_AFTER_EASTER_WED ;
constexpr auto ENDOF_PASHA = WEEK6_AFTER_EASTER_WED ;
constexpr auto ENDOF_PASCHA = WEEK6_AFTER_EASTER_WED ;
constexpr auto ENDOF_EASTER = WEEK6_AFTER_EASTER_WED ;
constexpr auto W6_A_E_THU = WEEK6_AFTER_EASTER_THU ;
constexpr auto ASCENSION = WEEK6_AFTER_EASTER_THU ;
constexpr auto W6_A_E_FRI = WEEK6_AFTER_EASTER_FRI ;
constexpr auto W6_A_E_SAT = WEEK6_AFTER_EASTER_SAT ;
constexpr auto SUN7_A_E =   SUN7_AFTER_EASTER      ;
constexpr auto W7_A_E_MON = WEEK7_AFTER_EASTER_MON ;
constexpr auto W7_A_E_TUE = WEEK7_AFTER_EASTER_TUE ;
constexpr auto W7_A_E_WED = WEEK7_AFTER_EASTER_WED ;
constexpr auto W7_A_E_THU = WEEK7_AFTER_EASTER_THU ;
constexpr auto W7_A_E_FRI = WEEK7_AFTER_EASTER_FRI ;
constexpr auto ENDOF_ASCENSION = WEEK7_AFTER_EASTER_FRI ;
constexpr auto W7_A_E_SAT = WEEK7_AFTER_EASTER_SAT ;
constexpr auto TRINITY_SAT = WEEK7_AFTER_EASTER_SAT ;
constexpr auto TRINITY_SUN = PENTECOST_SUN  ;
constexpr auto PENTECOST = PENTECOST_SUN  ;
constexpr auto HOLY_SPIRIT_DAY = PENTECOST_MON  ;
constexpr auto P_SUN = PENTECOST_SUN  ;
constexpr auto P_MON = PENTECOST_MON  ;
constexpr auto P_TUE = PENTECOST_TUE  ;
constexpr auto P_WED = PENTECOST_WED  ;
constexpr auto P_THU = PENTECOST_THU  ;
constexpr auto P_FRI = PENTECOST_FRI  ;
constexpr auto P_SAT = PENTECOST_SAT  ;
constexpr auto ENDOF_PENTECOST = PENTECOST_SAT  ;
constexpr auto ALL_SAINTS = SUN1_AFTER_PENTECOST ;
constexpr auto SUN1_A_P = SUN1_AFTER_PENTECOST ;
constexpr auto SUN2_A_P = SUN2_AFTER_PENTECOST ;
constexpr auto SUN3_A_P = SUN3_AFTER_PENTECOST ;
constexpr auto SUN4_A_P = SUN4_AFTER_PENTECOST ;
constexpr auto SAT_B_EX = SAT_BEFORE_EXALTATION ;
constexpr auto SUN_B_EX = SUN_BEFORE_EXALTATION ;
constexpr auto SAT_A_EX = SAT_AFTER_EXALTATION ;
constexpr auto SUN_A_EX = SUN_AFTER_EXALTATION ;
constexpr auto COUNCIL_7 = FATHERS_ECU_COUNCIL_7 ;
constexpr auto SAT_B_XMAS = SAT_BEFORE_CHRISTMAS ;
constexpr auto SUN_B_XMAS = SUN_BEFORE_CHRISTMAS ;
constexpr auto SAT_A_XMAS = SAT_AFTER_CHRISTMAS  ;
constexpr auto SAT_A_XMAS_R = SAT_AFTER_CHRISTMAS_READINGS ;
constexpr auto SUN_A_XMAS = SUN_AFTER_CHRISTMAS  ;
constexpr auto SUN_A_XMAS_R = SUN_AFTER_CHRISTMAS_READINGS  ;
constexpr auto SAT_B_NATIVITY = SAT_BEFORE_CHRISTMAS ;
constexpr auto SUN_B_NATIVITY = SUN_BEFORE_CHRISTMAS ;
constexpr auto SAT_A_NATIVITY = SAT_AFTER_CHRISTMAS  ;
constexpr auto SAT_A_NATIVITY_R = SAT_AFTER_CHRISTMAS_READINGS ;
constexpr auto SUN_A_NATIVITY = SUN_AFTER_CHRISTMAS  ;
constexpr auto SUN_A_NATIVITY_R = SUN_AFTER_CHRISTMAS_READINGS  ;
constexpr auto JUDG_SUN = DREAD_JUDGEMENT_SUN ;
constexpr auto FORGIVENESS_SUN = CHEESE_SUN ;
constexpr auto LENT_BEGIN = LENT_WEEK1_MON ;
constexpr auto LE_W1_MON = LENT_WEEK1_MON ;
constexpr auto LE_W1_TUE = LENT_WEEK1_TUE ;
constexpr auto LE_W1_WED = LENT_WEEK1_WED ;
constexpr auto LE_W1_THU = LENT_WEEK1_THU ;
constexpr auto LE_W1_FRI = LENT_WEEK1_FRI ;
constexpr auto LE_W1_SAT = LENT_WEEK1_SAT ;
constexpr auto CLEAN_MON = LENT_WEEK1_MON ;
constexpr auto CLEAN_TUE = LENT_WEEK1_TUE ;
constexpr auto CLEAN_WED = LENT_WEEK1_WED ;
constexpr auto CLEAN_THU = LENT_WEEK1_THU ;
constexpr auto CLEAN_FRI = LENT_WEEK1_FRI ;
constexpr auto THEODOR_SAT = LENT_WEEK1_SAT ;
constexpr auto FEODOR_SAT = LENT_WEEK1_SAT ;
constexpr auto LE_SUN1   = LENT_SUN1      ;
constexpr auto LE_W2_MON = LENT_WEEK2_MON ;
constexpr auto LE_W2_TUE = LENT_WEEK2_TUE ;
constexpr auto LE_W2_WED = LENT_WEEK2_WED ;
constexpr auto LE_W2_THU = LENT_WEEK2_THU ;
constexpr auto LE_W2_FRI = LENT_WEEK2_FRI ;
constexpr auto LE_W2_SAT = LENT_WEEK2_SAT ;
constexpr auto LE_SUN2   = LENT_SUN2      ;
constexpr auto GREGORY_PALAMA  = LENT_SUN2  ;
constexpr auto LE_W3_MON = LENT_WEEK3_MON ;
constexpr auto LE_W3_TUE = LENT_WEEK3_TUE ;
constexpr auto LE_W3_WED = LENT_WEEK3_WED ;
constexpr auto LE_W3_THU = LENT_WEEK3_THU ;
constexpr auto LE_W3_FRI = LENT_WEEK3_FRI ;
constexpr auto LE_W3_SAT = LENT_WEEK3_SAT ;
constexpr auto LE_SUN3   = LENT_SUN3      ;
constexpr auto LE_W4_MON = LENT_WEEK4_MON ;
constexpr auto LE_W4_TUE = LENT_WEEK4_TUE ;
constexpr auto LE_W4_WED = LENT_WEEK4_WED ;
constexpr auto LE_W4_THU = LENT_WEEK4_THU ;
constexpr auto LE_W4_FRI = LENT_WEEK4_FRI ;
constexpr auto LE_W4_SAT = LENT_WEEK4_SAT ;
constexpr auto LE_SUN4   = LENT_SUN4      ;
constexpr auto IOAN_LADDER = LENT_SUN4 ;
constexpr auto LE_W5_MON = LENT_WEEK5_MON ;
constexpr auto LE_W5_TUE = LENT_WEEK5_TUE ;
constexpr auto LE_W5_WED = LENT_WEEK5_WED ;
constexpr auto LE_W5_THU = LENT_WEEK5_THU ;
constexpr auto LE_W5_FRI = LENT_WEEK5_FRI ;
constexpr auto LE_W5_SAT = LENT_WEEK5_SAT ;
constexpr auto AKAFIST_SAT = LENT_WEEK5_SAT ;
constexpr auto LE_SUN5   = LENT_SUN5      ;
constexpr auto MARY_OF_EGYPT = LENT_SUN5 ;
constexpr auto LE_W6_MON = LENT_WEEK6_MON ;
constexpr auto LE_W6_TUE = LENT_WEEK6_TUE ;
constexpr auto LE_W6_WED = LENT_WEEK6_WED ;
constexpr auto LE_W6_THU = LENT_WEEK6_THU ;
constexpr auto LE_W6_FRI = LENT_WEEK6_FRI ;
constexpr auto LE_W6_SAT = LENT_WEEK6_SAT ;
constexpr auto PALM_MON = LENT_WEEK6_MON ;
constexpr auto PALM_TUE = LENT_WEEK6_TUE ;
constexpr auto PALM_WED = LENT_WEEK6_WED ;
constexpr auto PALM_THU = LENT_WEEK6_THU ;
constexpr auto PALM_FRI = LENT_WEEK6_FRI ;
constexpr auto PALM_SAT = LENT_WEEK6_SAT ;
constexpr auto LAZAR_SAT = LENT_WEEK6_SAT ;
constexpr auto LE_SUN7   = LENT_SUN7      ;
constexpr auto PALM_SUN   = LENT_SUN7     ;
constexpr auto LE_W7_MON = LENT_WEEK7_MON ;
constexpr auto LE_W7_TUE = LENT_WEEK7_TUE ;
constexpr auto LE_W7_WED = LENT_WEEK7_WED ;
constexpr auto LE_W7_THU = LENT_WEEK7_THU ;
constexpr auto LE_W7_FRI = LENT_WEEK7_FRI ;
constexpr auto LE_W7_SAT = LENT_WEEK7_SAT ;
constexpr auto GREAT_MON = LENT_WEEK7_MON ;
constexpr auto GREAT_TUE = LENT_WEEK7_TUE ;
constexpr auto GREAT_WED = LENT_WEEK7_WED ;
constexpr auto GREAT_THU = LENT_WEEK7_THU ;
constexpr auto GREAT_FRI = LENT_WEEK7_FRI ;
constexpr auto GREAT_SAT = LENT_WEEK7_SAT ;
constexpr auto G_MON = LENT_WEEK7_MON ;
constexpr auto G_TUE = LENT_WEEK7_TUE ;
constexpr auto G_WED = LENT_WEEK7_WED ;
constexpr auto G_THU = LENT_WEEK7_THU ;
constexpr auto G_FRI = LENT_WEEK7_FRI ;
constexpr auto G_SAT = LENT_WEEK7_SAT ;
constexpr auto LENT_END = LENT_WEEK7_SAT ;
constexpr auto SAT_BEFORE_THEOPHANY = SAT_BEFORE_BAPTISM ;
constexpr auto SUN_BEFORE_THEOPHANY = SUN_BEFORE_BAPTISM ;
constexpr auto SAT_AFTER_THEOPHANY  = SAT_AFTER_BAPTISM  ;
constexpr auto SUN_AFTER_THEOPHANY  = SUN_AFTER_BAPTISM  ;
constexpr auto SAT_B_THEOPHANY = SAT_BEFORE_BAPTISM ;
constexpr auto SUN_B_THEOPHANY = SUN_BEFORE_BAPTISM ;
constexpr auto SAT_A_THEOPHANY  = SAT_AFTER_BAPTISM  ;
constexpr auto SUN_A_THEOPHANY  = SUN_AFTER_BAPTISM  ;
constexpr auto SAT_B_BAPTISM   = SAT_BEFORE_BAPTISM ;
constexpr auto SUN_B_BAPTISM   = SUN_BEFORE_BAPTISM ;
constexpr auto SAT_A_BAPTISM    = SAT_AFTER_BAPTISM  ;
constexpr auto SUN_A_BAPTISM    = SUN_AFTER_BAPTISM  ;
constexpr auto RUS_MARTYRS    = NEW_MARTYRS_OF_RUSSIA  ;
constexpr auto HIERARCHS_3 = CONVENTION_OF_3_HIERARCHS;
constexpr auto FF_GOD_MEETING = FOREFEAST_GOD_MEETING;
constexpr auto AF_GOD_MEETING1 = AFTERFEAST_GOD_MEETING1 ;
constexpr auto AF_GOD_MEETING2 = AFTERFEAST_GOD_MEETING2 ;
constexpr auto AF_GOD_MEETING3 = AFTERFEAST_GOD_MEETING3 ;
constexpr auto AF_GOD_MEETING4 = AFTERFEAST_GOD_MEETING4 ;
constexpr auto AF_GOD_MEETING5 = AFTERFEAST_GOD_MEETING5 ;
constexpr auto AF_GOD_MEETING6 = AFTERFEAST_GOD_MEETING6 ;
constexpr auto IOAN_HEAD_FINDING_12 = JOHN_BAPTIST_HEAD_DISCOVERY_1_2 ;
constexpr auto IOAN_HEAD_FINDING_3 = JOHN_BAPTIST_HEAD_DISCOVERY_3 ;
constexpr auto MARTYRS_40 = HOLY_FORTY_MARTYRS_OF_SEBASTE ;
constexpr auto FF_ANNUNCIATION = FOREFEAST_GOD_MOTHER_ANNUNCIATION ;
constexpr auto ENDOF_ANNUNCIATION = ENDOF_GOD_MOTHER_ANNUNCIATION ;
constexpr auto MARTYR_GEORG = HOLY_GREAT_MARTYR_GEORGE ;
constexpr auto COUNCIL_1_6 = FATHERS_ECU_COUNCIL_1_6 ;


using MonthDay = std::pair<int,int> ;
MonthDay easter_date(const int year_number_in_great_indiction) ;
int apostol_fast_length(const int year_number_in_great_indiction) ;
bool is_date_of(const int year_number_in_great_indiction, const MonthDay date, const DayProperty property) ;
MonthDay find_date(const int year_number_in_great_indiction, const DayProperty property) ;

} // namespace great_indiction
