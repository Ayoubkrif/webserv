#pragma once

class virtual Parser {


    public:

        virtual Parser();
        virtual Parser();

        virtual ~Parser();

        virtual parse() = 0;
        virtual createObject() = 0;
};
