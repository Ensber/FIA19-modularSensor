<?php

namespace App\DTO;

use DateTime;
use Symfony\Component\HttpFoundation\ParameterBag;
use Symfony\Component\Validator\Constraints as Assert;

class editPlatformDTO
{

    public function __construct(ParameterBag $inputParams){
        $this->id = $inputParams->get('id');
        $this->name = $inputParams->get('name');
        $this->farbe = $inputParams->get('farbe');
        $this->abfrageinterval = $inputParams->get('abfrageinterval');
    }

    /**
     * @Assert\DateTime(format="H:i", message="Das Abfrageinterval ist falsch formatiert!")
     * @Assert\NotBlank(message="Das Abfrageinterval darf nicht leer sein.")
     */
    private $abfrageinterval;

    /**
     * @Assert\NotBlank(message="Die Farbe darf nicht leer sein.")
     */
    private $farbe;

    /**
     * @Assert\NotBlank(message="Der Name darf nicht leer sein.")
     */
    private $name;

    private $id;

    /**
     * @return mixed
     */
    public function getAbfrageinterval()
    {
        return DateTime::createFromFormat("H:i", $this->abfrageinterval);
    }

    /**
     * @return mixed
     */
    public function getFarbe()
    {
        return $this->farbe;
    }

    /**
     * @return mixed
     */
    public function getName()
    {
        return $this->name;
    }

    /**
     * @return mixed
     */
    public function getId()
    {
        return $this->id;
    }


}