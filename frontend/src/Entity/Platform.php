<?php

namespace App\Entity;

use Doctrine\ORM\Mapping as ORM;

/**
 * Platform
 *
 * @ORM\Table(name="Platform")
 * @ORM\Entity
 */
class Platform
{
    /**
     * @var int
     *
     * @ORM\Column(name="PL_ID", type="integer", nullable=false, options={"unsigned"=true})
     * @ORM\Id
     * @ORM\GeneratedValue(strategy="IDENTITY")
     */
    private $plId;

    /**
     * @var string|null
     *
     * @ORM\Column(name="Name", type="text", length=65535, nullable=true)
     */
    private $name;

    /**
     * @var \DateTime
     *
     * @ORM\Column(name="AbfrageInterval", type="time", nullable=false)
     */
    private $abfrageinterval;

    /**
     * @var \DateTime
     *
     * @ORM\Column(name="naechsteAbfrage", type="datetime", nullable=false, options={"default"="CURRENT_TIMESTAMP"})
     */
    private $naechsteabfrage = 'CURRENT_TIMESTAMP';

    /**
     * @var string
     *
     * @ORM\Column(name="Farbe", type="text", length=65535, nullable=false, options={"default"="blue"})
     */
    private $farbe = 'blue';

    /**
     * @return int
     */
    public function getPlId(): int
    {
        return $this->plId;
    }

    /**
     * @param int $plId
     */
    public function setPlId(int $plId): void
    {
        $this->plId = $plId;
    }

    /**
     * @return string|null
     */
    public function getName(): ?string
    {
        return $this->name;
    }

    /**
     * @param string|null $name
     */
    public function setName(?string $name): void
    {
        $this->name = $name;
    }

    /**
     * @return \DateTime
     */
    public function getAbfrageinterval(): \DateTime
    {
        return $this->abfrageinterval;
    }

    /**
     * @param \DateTime $abfrageinterval
     */
    public function setAbfrageinterval(\DateTime $abfrageinterval): void
    {
        $this->abfrageinterval = $abfrageinterval;
    }

    /**
     * @return \DateTime
     */
    public function getNaechsteabfrage()
    {
        return $this->naechsteabfrage;
    }

    /**
     * @param \DateTime $naechsteabfrage
     */
    public function setNaechsteabfrage($naechsteabfrage): void
    {
        $this->naechsteabfrage = $naechsteabfrage;
    }

    /**
     * @return string
     */
    public function getFarbe(): string
    {
        return $this->farbe;
    }

    /**
     * @param string $farbe
     */
    public function setFarbe(string $farbe): void
    {
        $this->farbe = $farbe;
    }


}
