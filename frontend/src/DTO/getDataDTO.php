<?php

namespace App\DTO;

use DateTime;
use Symfony\Component\HttpFoundation\ParameterBag;
use Symfony\Component\Validator\Constraints as Assert;

class getDataDTO
{
    /**
     * @Assert\DateTime(format="d.m.Y H:i", message="Das Startdatum ist falsch formatiert!")
     * @Assert\NotBlank(message="Das Startdatum darf nicht leer sein.")
     */
    private $begin;

    /**
     * @Assert\DateTime(format="d.m.Y H:i", message="Das Enddatum ist falsch formatiert!")
     * @Assert\NotBlank(message="Das Enddatum darf nicht leer sein.")
     */
    private $end;

    public function __construct(ParameterBag $inputParams)
    {
        $this->begin = $inputParams->get('begin');
        $this->end = $inputParams->get('end');
    }

    public function getBegin() : DateTime
    {
        return DateTime::createFromFormat('d.m.Y H:i', $this->begin);
    }

    public function getEnd() : DateTime
    {
        return DateTime::createFromFormat('d.m.Y H:i', $this->end);
    }
}