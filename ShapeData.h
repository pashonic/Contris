//   Contris  Copyright (C) 2009  Aaron Greene

//   This program is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.

//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.

//   You should have received a copy of the GNU General Public License
//   along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef SHAPEDATA_H_INCLUDED
#define SHAPEDATA_H_INCLUDED

struct Piece
{
    int rotation_Count;
    Tile_Color color;
    struct Rotation{int state[3][2];};
    Rotation rotations[4];
};

const Piece Piece_Data[7] =
                             {
                                //I Shape
                                {2, //Rotation Count
                                LIGHTBLUE,  //Color

                             {{{{0,-1},     //state 1
                                {0,1},
                                {0,2}}},

                              {{{-2,0},     //state 2
                                {-1,0},
                                {1,0}}},

                              {{{0,0},      //state 3
                                {0,0},
                                {0,0}}},

                              {{{0,0},      //state 4
                                {0,0},
                                {0,0}}}
                                }},

                                //J Shape
                                {4, //Rotation Count
                                DARKBLUE,   //Color

                             {{{{0,-1},     //state 1
                                {1,-1},
                                {0,1}}},

                              {{{-1,0},     //state 2
                                {1,0},
                                {-1,-1}}},

                              {{{0,1},      //state 3
                                {0,-1},
                                {-1,1}}},

                              {{{1,0},     //state 4
                                {-1,0},
                                {1,1}}}
                                }},

                                //L Shape
                                {4, //Rotation Count
                                ORANGE,     //Color

                             {{{{-1,-1},    //state 1
                                {0,-1},
                                {0,1}}},

                              {{{-1,0},     //state 2
                                {-1,1},
                                {1,0}}},

                              {{{0,-1},     //state 3
                                {0,1},
                                {1,1}}},

                              {{{-1,0},     //state 4
                                {1,0},
                                {1,-1}}}
                                }},

                                //O Shape
                                {1, //Rotation Count
                                YELLOW,     //Color

                             {{{{-1,0},     //state 1
                                {-1,1},
                                {0,1}}},

                              {{{0,0},      //state 2
                                {0,0},
                                {0,0}}},

                              {{{0,0},      //state 3
                                {0,0},
                                {0,0}}},

                              {{{0,0},      //state 4
                                {0,0},
                                {0,0}}}
                                }},

                                //S Shape
                                {2, //Rotation Count
                                GREEN,      //Color

                             {{{{1,0},      //state 1
                                {0,1},
                                {-1,1}}},

                              {{{0,-1},     //state 2
                                {1,0},
                                {1,1}}},

                              {{{0,0},      //state 3
                                {0,0},
                                {0,0}}},

                              {{{0,0},      //state 4
                                {0,0},
                                {0,0}}}
                                }},

                                //T Shape
                                {4, //Rotation Count
                                PURPLE,     //Color

                             {{{{0,-1},     //state 1
                                {1,0},
                                {-1,0}}},

                              {{{0,-1},     //state 2
                                {-1,0},
                                {0,1}}},

                              {{{1,0},      //state 3
                                {-1,0},
                                {0,1}}},

                              {{{0,-1},     //state 4
                                {1,0},
                                {0,1}}}
                                }},

                                //Z Shape
                                {2, //Rotation Count
                                RED,        //Color

                             {{{{-1,0},     //state 1
                                {0,1},
                                {1,1}}},

                              {{{1,-1},     //state 2
                                {1,0},
                                {0,1}}},

                              {{{0,0},      //state 3
                                {0,0},
                                {0,0}}},

                              {{{0,0},      //state 4
                                {0,0},
                                {0,0}}}
                                }}
                            };
#endif
